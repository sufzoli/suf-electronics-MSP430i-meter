#include <msp430.h>
// #include <legacymsp430.h>
// #include <stdio.h>

#include "uart.h"
#include "fifo.h"
#include "text.h"

// uart tx/rx FIFO
fifo tx;
fifo rx;


volatile unsigned char rx_linenum = 0;

// define putchar for link stdio with the UART
int putchar(int c)
{
  uart_putc(c);
  return 1;
}

// init hardware uart
void uart_init(void)
{
  // init FIFO
  fifo_init(&tx);
  fifo_init(&rx);

  P1SEL0 |=   BIT2 | BIT3;            // P1.2/3 eUSCI_A Function
  P1SEL1 &= ~(BIT2 | BIT3);

  UCA0CTL1 |= UCSWRST;                // Hold eUSCI in reset
  // select SMCLK                 
  UCA0CTL1 |= UCSSEL_2;

  UCA0BR0   = 142;                    // 115200 baud
  UCA0BR1   = 0;
  UCA0MCTLW = 0x2200;                 // 16.384MHz/115200 = 142.22 (See UG)

  // Initialize USCI state machine
  UCA0CTL1 &= ~UCSWRST;

  UCA0IE  |= UCRXIE;                 // Enable RX interrupt
//   UCA0IE   |= UCRXIE | UCTXIE;                 // Enable RX and TX interrupt

}

unsigned char uart_getc()
{
    unsigned char c;
    c = fifo_getc(&rx);
    if(c == EOL)
    {
        rx_linenum--;
    }
    return c;
}

void uart_getln(volatile unsigned char buf[])
{
    volatile unsigned char i,c;
    i=0;
    do
    {
        c = uart_getc();
        if(c == EOL)
            c = 0;
        buf[i] = c;
        i++;
    }
    while(c != 0);
}

void uart_putln(volatile unsigned char buf[])
{
    volatile unsigned char i;
    for(i=0; buf[i] != 0; i++)
    {
        uart_putc(buf[i]);
    }
    uart_putc(0x0D);
}

unsigned char uart_numln()
{
    return rx_linenum;
}

void uart_putc(volatile unsigned char c)
{
    while (!(UCA0IFG&UCTXIFG)); // USCI_A0 TX buffer ready?
    UCA0TXBUF = c;
    /*
    if(tx.size == 0)
    {
        if(!(UCA0IFG & UCTXIFG))
        {
            UCA0TXBUF = c;
            return;
        }
    }
    // add char in fifo, wait if tx fifo is full
    while (fifo_putc(&tx,c) == EOT);
    */
}

void uart_puthex(unsigned char c)
{
    uart_putc(hex[c >> 4]);
    uart_putc(hex[c & 0x0F]);
}

// wait tx buffer is clean
void uart_wait_tx(void)
{
  while(fifo_size(&tx) != 0);
}

unsigned char uart_rx_size()
{
    return rx.size;
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
    char c;
    // __disable_interrupt();
    switch(__even_in_range(UCA0IV,USCI_UART_UCTXCPTIFG))
    {
        case USCI_NONE:
            break;
        case USCI_UART_UCRXIFG:
              c = UCA0RXBUF;
              // store char in FIFO
              if (rx.size < FIFO_BUFFER_SIZE)
              {
                  if(c == EOL)
                  {
                      rx_linenum++;
                  }
                rx.data[rx.waddr] = c;
                rx.size++;
                if (rx.waddr < (FIFO_BUFFER_SIZE - 1))
                  rx.waddr++;
                else
                  rx.waddr =0;
              }
            break;
        case USCI_UART_UCTXIFG:
            // check fifo level
            if (tx.size > 0)
            {
              // empty fifo: stop tx interrupt
              //  UCA0IE &= ~UCTXIE;
/*            }
            else
            {
            */
              // read current value
              UCA0TXBUF = tx.data[tx.raddr];
              tx.size--;
              // set read pointer
              tx.raddr = (tx.raddr < (FIFO_BUFFER_SIZE - 1)) ? tx.raddr + 1 : 0;
            }
            break;
        case USCI_UART_UCSTTIFG:
            break;
        case USCI_UART_UCTXCPTIFG:
            break;
        default: break;
    }
    // __enable_interrupt();
}


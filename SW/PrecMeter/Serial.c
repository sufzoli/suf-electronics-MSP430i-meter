/*
 * Serial.c
 *
 *  Created on: 2016. dec. 21.
 *      Author: zoli
 */

#include <msp430.h>


// char text[] ="Hello World!";

char hex[] = "0123456789ABCDEF";

unsigned char _tx_buff[20];
unsigned char _tx_head;
unsigned char _tx_tail;


/* Very simple queue
 * These are FIFO queues which discard the new data when full.
 *
 * Queue is empty when in == out.
 * If in != out, then
 *  - items are placed into in before incrementing in
 *  - items are removed from out before incrementing out
 * Queue is full when in == (out-1 + QUEUE_SIZE) % QUEUE_SIZE;
 *
 * The queue will hold QUEUE_ELEMENTS number of items before the
 * calls to QueuePut fail.
 */

/* Queue structure */
#define TX_FIFO_ELEMENTS 100
#define TX_FIFO_SIZE (TX_FIFO_ELEMENTS + 1)
volatile char TX_Fifo[TX_FIFO_SIZE];
volatile char TX_FifoIn, TX_FifoOut;

void TX_FifoInit(void)
{
    TX_FifoIn = TX_FifoOut = 0;
}

int TX_FifoPut(char new)
{
    if(TX_FifoIn == (( TX_FifoOut - 1 + TX_FIFO_SIZE) % TX_FIFO_SIZE))
    {
        return -1; /* Queue Full*/
    }

    TX_Fifo[TX_FifoIn] = new;

    TX_FifoIn = (TX_FifoIn + 1) % TX_FIFO_SIZE;

    return 0; // No errors
}

int TX_FifoGet(char *old)
{
    if(TX_FifoIn == TX_FifoOut)
    {
        return -1; /* Queue Empty - nothing to get*/
    }

    *old = TX_Fifo[TX_FifoOut];

    TX_FifoOut = (TX_FifoOut + 1) % TX_FIFO_SIZE;

    return 0; // No errors
}

char serial_TX_full()
{
    return (TX_FifoIn == (( TX_FifoOut - 1 + TX_FIFO_SIZE) % TX_FIFO_SIZE)) ? 1 : 0;
}

char serial_TX_empty()
{
    return (TX_FifoIn == TX_FifoOut) ? 1 : 0;
}

void serial_Init(void)
{
    TX_FifoInit();
    P1SEL0 |=   BIT2 | BIT3;            // P1.2/3 eUSCI_A Function
    P1SEL1 &= ~(BIT2 | BIT3);

    UCA0CTL1 |= UCSWRST;                // Hold eUSCI in reset
    UCA0CTL1 |= UCSSEL_2;               // SMCLK
    UCA0BR0   = 142;                    // 115200 baud
    UCA0BR1   = 0;
    UCA0MCTLW = 0x2200;                 // 16.384MHz/115200 = 142.22 (See UG)
    UCA0CTL1 &= ~UCSWRST;               // Release from reset
    UCA0IE   |= UCRXIE | UCTXIE;                 // Enable RX and TX interrupt
}

int serial_SendChar(char value)
{
    int retvalue = 0;
    if((TX_FifoIn != TX_FifoOut) || (UCA0IFG & UCTXIFG)) // the fifo isn't empty or TX interrupt pending
    {
        retvalue = TX_FifoPut(value); // put char into the fifo
    }
    else
    {
        UCA0TXBUF = value; // send char
    }
    return retvalue;
}
void serial_SendString(char text[])
{
    int errcode;
    char i;
    for(i=0;text[i] != 0;i++)
    {
        do
        {
            errcode = serial_SendChar(text[i]);
        } while(errcode != 0);
    }
}

void serial_SendHex(unsigned char value)
{
    int errcode;
    volatile unsigned char temp;
    temp = value;
    do
    {
        errcode = serial_SendChar(hex[temp >> 4]);
    } while(errcode != 0);
    do
    {
        errcode = serial_SendChar(hex[temp & 0x0F]);
    } while(errcode != 0);
}


/*
void serial_SendString(char[] text)
{

    int errcode;
    for(i=0;text[i] != 0;i++)
    {
        do
        {
            errcode = serial_SendChar(text[i]);
        } while(errcode != 0)
    }

}
*/

// Echo back RXed character, confirm TX buffer is ready first
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
    int errcode;
    char value;

    switch(__even_in_range(UCA0IV,USCI_UART_UCTXCPTIFG))
    {
        case USCI_NONE:
            break;
        case USCI_UART_UCRXIFG:

 //                while (!(UCA0IFG&UCTXIFG)); // USCI_A0 TX buffer ready?
 //                UCA0TXBUF = UCA0RXBUF;      // TX -> RXed character
/*
            for(i=0;text[i] != 0;i++)
            {
                while (!(UCA0IFG&UCTXIFG)); // USCI_A0 TX buffer ready?
                UCA0TXBUF = text[i];
            }
*/
            break;
        case USCI_UART_UCTXIFG:
            // Place of the next char transmit
            errcode = TX_FifoGet(&value);
            if(errcode == 0) // no error, the return value is valid
            {
                UCA0TXBUF = value;
            }
            break;
        case USCI_UART_UCSTTIFG:
            break;
        case USCI_UART_UCTXCPTIFG:
            break;
        default: break;
    }
}


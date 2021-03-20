#include <msp430.h> 
#include "sd24.h"
#include "Serial.h"

/*
 * main.c
 */

// char text[] ="Hello World!\r\n";

volatile char ch_codes[] = "abcd";


int main(void)
{
    unsigned char i,j;
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    serial_Init();
/*
    P1SEL0 |=   BIT2 | BIT3;            // P1.2/3 eUSCI_A Function
    P1SEL1 &= ~(BIT2 | BIT3);

    UCA0CTL1 |= UCSWRST;                // Hold eUSCI in reset
    UCA0CTL1 |= UCSSEL_2;               // SMCLK
    UCA0BR0   = 142;                    // 115200 baud
    UCA0BR1   = 0;
    UCA0MCTLW = 0x2200;                 // 16.384MHz/115200 = 142.22 (See UG)
    UCA0CTL1 &= ~UCSWRST;               // Release from reset
    // UCA0IE   |= UCRXIE;                 // Enable RX interrupt
*/
    sd24_Init(0);
    char* tmp_str;

    while(1)
    {
        //sd24_ClearFlag();
        sd24_Aquire();
        // while(!sd24_Ready());
        for(i=0;i<4;i++)
        {
            serial_SendChar(ch_codes[i]);
            tmp_str = sd24_GetHex(i);
            for(j=0;j<6;j++)
            {
                serial_SendChar(tmp_str[j]);
            }
            serial_SendChar('\r');
            serial_SendChar('\n');
        }
        /*
        for(i=0;text[i] != 0;i++)
        {
            while (!(UCA0IFG&UCTXIFG)); // USCI_A0 TX buffer ready?
            UCA0TXBUF = text[i];
        }
        */
    }
	
// 	return 0;
}

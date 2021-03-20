#include <msp430.h>
#include "Serial.h"
#include "sd24.h"

/*
 * main.c
 */
char hwtext[] ="HW!\n";
volatile char ch_codes[] = "abcd";
void main(void)
{
    volatile unsigned int wvalue;
    unsigned char i,j;
    int errcode;

    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    __bis_SR_register(GIE);             // Enable interrupts

    sd24_Init();
    serial_Init();

    while(1)                   // Main loop (not determinded if it required for something)
    {
        while(!sd24_convready);
        for(i=0;i<4;i++)
        {
            // serial_SendChar(ch_codes[i]);
            do
            {
                errcode = serial_SendChar(ch_codes[i]);
            } while(errcode != 0);
            for(j=0;j<3;j++)
            {
                serial_SendHex(sd24_results[i*3+j]);
            }
            do
            {
                errcode = serial_SendChar('\r');
            } while(errcode != 0);
            do
            {
                errcode = serial_SendChar('\n');
            } while(errcode != 0);
        }
        sd24_convready = 0;
        /*
        // while(!sd24_convready);
        for(i=0;i<4;i++)
        {
            serial_SendChar(ch_codes[i]);
            for(j=0;j<3;j++)
            {
                serial_SendHex(sd24_results[i*3+j]);
            }
            serial_SendString("\r\n");
        }
        // sd24_convready = 0;
        */
        /*
        wvalue = 0xABCD;
        serial_SendHex(wvalue >> 8);
        serial_SendHex(wvalue & 0x00FF);
        wvalue = 0xCDEF;
        serial_SendHex(wvalue & 0x00FF);
        serial_SendString("\r\n");
        */
    }
}

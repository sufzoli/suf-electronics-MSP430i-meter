#include <msp430.h> 
#include "uart.h"
#include "pwm_dac.h"
#include "wdt.h"
#include "text.h"
#include "sd24.h"

/*
 * main.c
 */

volatile unsigned char buff[20];
const char ch_codes[] = "abcd";


void main(void)
{
    volatile unsigned char i,j;
    volatile unsigned char* tmp_str;
    wdt_init();
    CSCTL1 = 0; // SMCLK = DCO
    uart_init();
    pwm_dac_init();
    sd24_Init();
    __bis_SR_register(GIE); // Enable interrupts

    while(1)
    {
        if(uart_numln() > 0)
        {
            uart_getln(buff);
            switch(buff[0])
            {
                case 'g':
                    pwm_set(2, hex2uint(&buff[1]));
                    break;
                case 'h':
                    pwm_set(3, hex2uint(&buff[1]));
                    break;
                default:
                    break;
            }
            // uart_putln(buff);
        }
        if(wdt_pending() == 1)
        {
            wdt_reset();
            // sd24_Aquire();
            for(i=0;i<4;i++)
            {
                uart_putc(ch_codes[i]);
                /*
                tmp_str = sd24_GetHex(i);
                for(j=0;j<6;j++)
                {
                    uart_putc(tmp_str[j]);
                }
                */
                uart_putc(0x0D);
                uart_putc(0x0A);
            }

        }
    }
}

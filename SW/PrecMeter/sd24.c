/*
 * sd24.c
 *
 *  Created on: 2016. dec. 28.
 *      Author: Administrator
 */

#include <msp430.h>
#include "sd24.h"

volatile unsigned char sd24_results[12];
volatile unsigned char sd24_convready;

void sd24_Init()
{
    sd24_convready = 0;
    SD24CTL = SD24REFS;                            // Internal ref
    SD24CCTL0  |= SD24GRP | SD24DF;                // Group with CH1
    SD24CCTL1  |= SD24GRP | SD24DF;                // Group with CH2
    SD24CCTL2  |= SD24GRP | SD24DF;                // Group with CH3
    SD24CCTL3  |= SD24IE | SD24DF;                 // Enable interrupt

    __delay_cycles(3200);                          // Delay ~200us for 1.2V ref to settle

     SD24CCTL3 |= SD24SC;                           // Set bit to start conversion
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=SD24_VECTOR
__interrupt void SD24_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(SD24_VECTOR))) SD24_ISR (void)
#else
#error Compiler not supported!
#endif
{
    volatile unsigned int result_temp;
    switch (__even_in_range(SD24IV,SD24IV_SD24MEM3)) {
        case SD24IV_NONE: break;
        case SD24IV_SD24OVIFG: break;
        case SD24IV_SD24MEM0: break;
        case SD24IV_SD24MEM1: break;
        case SD24IV_SD24MEM2: break;
        case SD24IV_SD24MEM3:
            SD24CCTL0 &= ~SD24LSBACC;
            result_temp = SD24MEM0;
            sd24_results[0] = result_temp >> 8;
            sd24_results[1] = result_temp & 0x00FF;
            SD24CCTL0 |= SD24LSBACC;
            sd24_results[2] = SD24MEM0 & 0x00FF;

            SD24CCTL1 &= ~SD24LSBACC;
            result_temp = SD24MEM1;
            sd24_results[3] = result_temp >> 8;
            sd24_results[4] = result_temp & 0x00FF;
            SD24CCTL0 |= SD24LSBACC;
            sd24_results[5] = SD24MEM1 & 0x00FF;

            SD24CCTL2 &= ~SD24LSBACC;
            result_temp = SD24MEM2;
            sd24_results[6] = result_temp >> 8;
            sd24_results[7] = result_temp & 0x00FF;
            SD24CCTL0 |= SD24LSBACC;
            sd24_results[8] = SD24MEM2 & 0x00FF;

            SD24CCTL3 &= ~SD24LSBACC;
            result_temp = SD24MEM3;
            sd24_results[9] = result_temp >> 8;
            sd24_results[10] = result_temp & 0x00FF;
            SD24CCTL0 |= SD24LSBACC;
            sd24_results[11] = SD24MEM3 & 0x00FF;

            sd24_convready = 1;
            break;
        default: break;
    }
}

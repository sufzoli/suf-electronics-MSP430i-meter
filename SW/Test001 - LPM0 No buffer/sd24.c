/*
 * sd24.c
 *
 *  Created on: 2016. dec. 28.
 *      Author: Administrator
 */

#include <msp430.h>
#include "sd24.h"

#define SD24_AVERAGE 7

volatile static signed long sd24_results[4];
volatile static unsigned char sd24_convready;
const char hex[] = "0123456789ABCDEF";
volatile char sd24_result_hex[] = "      ";

void sd24_Init()
{
    sd24_convready = 0;
    SD24CTL = SD24REFS;                            // Internal ref

    SD24CCTL0  |= SD24SNGL | SD24GRP | SD24DF;                // Group with CH1
    SD24CCTL1  |= SD24SNGL | SD24GRP | SD24DF;                // Group with CH2
    SD24CCTL2  |= SD24SNGL | SD24GRP | SD24DF;                // Group with CH3
    SD24CCTL3  |= SD24SNGL | SD24IE | SD24DF;                 // Enable interrupt

    __delay_cycles(3200);                          // Delay ~200us for 1.2V ref to settle

//     SD24CCTL3 |= SD24SC;                           // Set bit to start conversion
}

void sd24_Start(unsigned char lpm)
{
    SD24CCTL3 |= SD24SC;                    // Set bit to start conversion
     __bis_SR_register((lpm ? 0 : LPM0_bits) | GIE);     // Enter LPM0 w/ interrupts
}

void sd24_Aquire()
{
    unsigned char i;
    for(i=0;i<4;i++)
    {
        sd24_results[i]=0;
    }

    for(i = 0; i < (1 << SD24_AVERAGE); i++)
    {
        sd24_convready = 0;
        SD24CCTL3 |= SD24SC;                    // Set bit to start conversion
        __bis_SR_register(LPM0_bits | GIE);     // Enter LPM0 w/ interrupts
        while(!sd24_convready);
    }
    // Acquisition ready
    for(i=0;i<4;i++)
    {
//        sd24_results[i] = sd24_2powerDiv(sd24_results[i],SD24_AVERAGE);
        sd24_results[i] >>= SD24_AVERAGE;
    }
}

char* sd24_GetHex(unsigned char ch)
{
    int i;
//    char sd24_result[] = "      ";
    volatile long value = sd24_results[ch];
    for(i=5;i>=0;i--)
    {
        sd24_result_hex[i] = hex[value & 0x0000000F];
        value >>= 4;
    }
    return sd24_result_hex;
}
/*
unsigned char sd24_Ready()
{
    return sd24_convready;
}
*/
/*
void sd24_ClearFlag()
{
    sd24_convready = 0;
}
*/
signed long sd24_ResultToInt32(unsigned int high, unsigned int low)
{
    volatile long result;
    result = high;
    result <<= 8;
    result |= low & 0x00FF;
    return (result & 0x00800000) ? 0xFF000000 | result: result;
//            (result & 0x007FFFFF) | ((result & 0x00800000) << 8);
}

signed long sd24_2powerDiv(long value,unsigned char power)
{
    // this is wrong, must be changed
    return ((value & 0x7FFFFFFF) >> power) | (value & 0x80000000);
}

signed long sd24_CompactTo24(long value)
{
    return (value & 0x7FFFFF) | ((value & 0x80000000) >> 8);
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
    switch (__even_in_range(SD24IV,SD24IV_SD24MEM3))
    {
        case SD24IV_NONE: break;
        case SD24IV_SD24OVIFG: break;
        case SD24IV_SD24MEM0: break;
        case SD24IV_SD24MEM1: break;
        case SD24IV_SD24MEM2: break;
        case SD24IV_SD24MEM3:
            SD24CCTL0 &= ~SD24LSBACC;
            result_temp = SD24MEM0;
            SD24CCTL0 |= SD24LSBACC;
            sd24_results[0] += sd24_ResultToInt32(result_temp, SD24MEM0);

            SD24CCTL1 &= ~SD24LSBACC;
            result_temp = SD24MEM1;
            SD24CCTL1 |= SD24LSBACC;
            sd24_results[1] += sd24_ResultToInt32(result_temp, SD24MEM1);

            SD24CCTL2 &= ~SD24LSBACC;
            result_temp = SD24MEM2;
            SD24CCTL2 |= SD24LSBACC;
            sd24_results[2] += sd24_ResultToInt32(result_temp, SD24MEM2);

            SD24CCTL3 &= ~SD24LSBACC;
            result_temp = SD24MEM3;
            SD24CCTL3 |= SD24LSBACC;
            sd24_results[3] += sd24_ResultToInt32(result_temp, SD24MEM3);

            sd24_convready = 1;
            __bic_SR_register_on_exit(LPM0_bits); // Wake up
            break;
        default: break;
    }
}

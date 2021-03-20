#include <msp430.h>
#include "pwm_dac.h"


void pwm_dac_init()
{
    // Using TimerA1 module, TA1.1 and TA1.2 outputs as PWM channels

    // Set timer output for the PWM
    P2DIR |= BIT1 + BIT2;
    P2SEL0 |= BIT1 + BIT2;
    P2SEL1 &= ~(BIT1 + BIT2);

    // Timer init
    TA1CTL = TASSEL_2 + MC_1; // SMCLK, start in continous mode
    TA1CCTL1 = OUTMOD_7;
    TA1CCTL2 = OUTMOD_7;
    TA1CCR0 = 0xFFFF;
    TA1CCR1 = 0x7FFF;
    TA1CCR2 = 0x3FFF;
}

void pwm_set(unsigned char ch, unsigned int value)
{
    switch(ch)
    {
        case 2:
            TA1CCR1 = value;
            break;
        case 3:
            TA1CCR2 = value;
            break;
        default:
            break;
    }
}

#include <msp430.h> 

/*
 * main.c
 */
int main(void)
{
    WDTCTL = WDT_MDLY_8;	// WDT as Intervall timer
    CSCTL1 = 0; // SMCLK = DCO
    P2DIR |= BIT3;
    IE1 |= WDTIE;
    __bis_SR_register(GIE);
    while(1);
}

#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
    P2OUT ^= BIT3;                    // Toggle P2.3

}

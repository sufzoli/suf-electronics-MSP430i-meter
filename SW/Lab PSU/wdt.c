/*
 * wdt.c
 *
 *  Created on: 2017. febr. 7.
 *      Author: zoli
 */
#include <msp430.h>
#include "wdt.h"

volatile unsigned char _wdt_pending;

void wdt_init()
{
    WDTCTL = WDT_MDLY_8;    // WDT as Intervall timer
    IE1 |= WDTIE;
    _wdt_pending = 0;
}

unsigned char wdt_pending()
{
    return _wdt_pending;
}

void wdt_reset()
{
    _wdt_pending = 0;
}

#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
    _wdt_pending = 1;
}

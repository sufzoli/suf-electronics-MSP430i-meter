/*
 * wdt.h
 *
 *  Created on: 2017. febr. 7.
 *      Author: zoli
 */

#ifndef WDT_H_
#define WDT_H_

void wdt_init();
unsigned char wdt_pending();
void wdt_reset();

#endif /* WDT_H_ */

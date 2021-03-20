/*
 * sd24.h
 *
 *  Created on: 2016. dec. 28.
 *      Author: Administrator
 */

#ifndef SD24_H_
#define SD24_H_

extern volatile unsigned char sd24_results[12];
extern volatile unsigned char sd24_convready;

void sd24_Init();

#endif /* SD24_H_ */

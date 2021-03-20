/*
 * sd24.h
 *
 *  Created on: 2016. dec. 28.
 *      Author: Administrator
 */

#ifndef SD24_H_
#define SD24_H_

void sd24_Init();
void sd24_Start(unsigned char lpm);
void sd24_ClearFlag();
void sd24_Aquire();
signed long sd24_2powerDiv(long value,unsigned char power);
char* sd24_GetHex(unsigned char ch);

#endif /* SD24_H_ */

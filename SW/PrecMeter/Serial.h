/*
 * Serial.h
 *
 *  Created on: 2016. dec. 21.
 *      Author: zoli
 */

#ifndef SERIAL_H_
#define SERIAL_H_

void serial_Init(void);
int serial_SendChar(char value);
void serial_SendString(char text[]);
void serial_SendHex(unsigned char value);

#endif /* SERIAL_H_ */

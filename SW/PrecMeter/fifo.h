/*
 * fifo.h
 *
 *  Created on: 2016. dec. 30.
 *      Author: Administrator
 */

#ifndef FIFO_H_
#define FIFO_H_

typedef struct
{
     char * buf;
     unsigned int head;
     unsigned int tail;
     unsigned int size;
} fifo_t;

void fifo_init(fifo_t * f, char * buf, int size);
unsigned int fifo_readchar(fifo_t * f, char *value);
unsigned int fifo_writechar(fifo_t * f, char value);


#endif /* FIFO_H_ */

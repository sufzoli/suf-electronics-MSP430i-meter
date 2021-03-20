/*
 * queue.h
 *
 *  Created on: 2017. febr. 11.
 *      Author: zoli
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#define QUEUE_SIZE  20

// QUEUE struct
typedef struct
{
    volatile unsigned char head;
    volatile unsigned char tail;
    volatile unsigned char data[QUEUE_SIZE];
} queue;

void queue_init(queue * _queue);

#endif /* QUEUE_H_ */

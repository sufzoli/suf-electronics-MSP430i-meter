/*
 * queue.c
 *
 *  Created on: 2017. febr. 11.
 *      Author: zoli
 */
#include "queue.h"

// Initialize the queue
void queue_init(queue * _queue)
{
    // clear the queue pointers
    _queue->head = 0;
    _queue->tail = 0;
}

unsigned char _queue_count(queue * _queue)
{
    return (_queue->head < _queue->tail ? QUEUE_SIZE : 0) + _queue->head - _queue->tail;
}


signed char queue_dequeue_char(queue * _queue, unsigned char * buff)
{
    if(_queue_count(_queue) > 0)
    {
        buff = _queue->data[_queue->tail];
        _queue->tail = (_queue->tail < QUEUE_SIZE-1) ? _queue->tail + 1 : 0;
        return 0;
    }
    return -1;
}

signed char queue_enqueue_char(queue * _queue, unsigned char value)
{
    if(_queue_count(_queue) < QUEUE_SIZE)
    {
        _queue->data[_queue->head] = value;
        _queue->head = (_queue->head < QUEUE_SIZE-1) ? _queue->head + 1 : 0;
        return 0;
    }
    return -1;
}

signed char queue_sdequeue_char(queue * _queue, unsigned char * buff)
{
    signed char retvalue;
    unsigned short save_sr;
    save_sr = __bic_SR_register(GIE);
    if(_queue_count(_queue) > 0)
    {
        buff = _queue->data[_queue->tail];
        _queue->tail = (_queue->tail < QUEUE_SIZE-1) ? _queue->tail + 1 : 0;
        retvalue = 0;
    }
    else
    {
        retvalue = -1;
    }
    __bis_SR_register(save_sr & GIE);
    return retvalue;
}

signed char queue_senqueue_char(queue * _queue, unsigned char value)
{
    signed char retvalue;
    unsigned short save_sr;
    save_sr = __bic_SR_register(GIE);
    if(_queue_count(_queue) < QUEUE_SIZE)
    {
        _queue->data[_queue->head] = value;
        _queue->head = (_queue->head < QUEUE_SIZE-1) ? _queue->head + 1 : 0;
        retvalue = 0;
    }
    else
    {
        retvalue = -1;
    }
    __bis_SR_register(save_sr & GIE);
    return retvalue;
}

/* 
Simple fifo struct access functions


first parameter of evry function is a pointer to the fifo struct (see fifo.h).

example :
fifo_getchar(&thefifostruct);


fifo design: 
read ptr  data array  write ptr
          |  max   |
          |  ...   |
          |   2    |
          |   1    |
raddr  -> |   0    | <- waddr

Code under GPLv2.
Share, it's happiness !
*/

#include <msp430.h> 
// #include <stdlib.h>
// #include <stdio.h>
#include "fifo.h"

/**
 * Init FIFO struct.
 *
 */
void fifo_init(fifo *_fifo)
{
  _fifo->size  = 0;
  _fifo->raddr = 0;
  _fifo->waddr = 0;
}

/**
 * Read one character from FIFO.
 *
 * @return	current character or EOF if FIFO empty
 */
unsigned char fifo_getc(fifo *_fifo)
{
    unsigned char c;
    if (_fifo->size == 0)
    {
      return EOT;
    }
    __disable_interrupt();
    // read current value
    c = _fifo->data[_fifo->raddr];
    _fifo->size--;
    // set read pointer
    _fifo->raddr = (_fifo->raddr < (FIFO_BUFFER_SIZE - 1)) ? _fifo->raddr + 1 : 0;
    __enable_interrupt();
    return c;
}

/**
 * Write one character to FIFO.
 *
 * @return	0 if write ok or EOT if FIFO full
 */
unsigned char fifo_putc(fifo *_fifo, unsigned char c)
{
  // check fifo level
  if (_fifo->size >= FIFO_BUFFER_SIZE)
  {
    return EOT;
  }
  __disable_interrupt();
  // write current value
  _fifo->data[_fifo->waddr] = c;
  _fifo->size++;
  // set write pointer
  _fifo->waddr = (_fifo->waddr < (FIFO_BUFFER_SIZE - 1)) ? _fifo->waddr + 1 : 0;
  __enable_interrupt();
  return 0;
}

unsigned char fifo_is_full(fifo *_fifo)
{
    return _fifo->size >= FIFO_BUFFER_SIZE;
}

/**
 * Safe access to size of the FIFO.
 *
 * @return	number of byte in FIFO
 */
unsigned char fifo_size(fifo *_fifo)
{
  unsigned char size;
  // __disable_interrupt();
  size = _fifo->size;
  // __enable_interrupt();
  return size;
}

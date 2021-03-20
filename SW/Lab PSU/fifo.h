#ifndef __FIFO_H
#define __FIFO_H

#define FIFO_BUFFER_SIZE 32

#define EOT 4

// FIFO struct
typedef struct 
{
  volatile unsigned char data[FIFO_BUFFER_SIZE];
  volatile unsigned char size;
  volatile unsigned char raddr;
  volatile unsigned char waddr;
} fifo;

// FIFO access routines
void fifo_init(fifo *_fifo);
unsigned char fifo_getc(fifo *_fifo);
unsigned char fifo_putc(fifo *_fifo, unsigned char c);
unsigned char fifo_size(fifo *_fifo);
unsigned char fifo_is_full(fifo *_fifo);

#endif 

#ifndef __UART_H
#define __UART_H

#define EOL 0x0D

/*
 * initialize soft UART
 */
void uart_init(void);

/*
 * read one character from UART blocking.
 *
 * @return	character received 
 */
unsigned char uart_getc(void);

void uart_getln(volatile unsigned char buf[]);
void uart_putln(volatile unsigned char buf[]);
unsigned char uart_numln();

/*
 * write one chracter to the UART blocking.
 *
 * @param[in]	*c	the character to write
 */
void uart_putc(volatile unsigned char c);

/*
 * wait tx buffer is clean (= tx fifo empty)
 */
void uart_wait_tx(void);
void uart_puthex(unsigned char c);
unsigned char uart_rx_size();


#endif

#ifndef _IO_H
#define _IO_H

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t val);
void io_wait();

#endif
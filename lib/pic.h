#ifndef PIC_H
#define PIC_H

#include <stdint.h>

#define PIC1		0x20
#define PIC2		0xA0
#define PIC_OFFSET 	0x20

void pic_send_eoi(uint8_t irq);
void pic_remap(int offset1, int offset2);

#endif
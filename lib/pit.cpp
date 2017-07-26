#include "pit.h"
#include "io.h"

static uint32_t input_hz = 11931820;

void init_pit(int hz) {
	int divisor = input_hz / hz;       /* Calculate our divisor */
    outb(0x43, 0x36);             /* Set our command byte 0x36 */
    outb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    outb(0x40, divisor >> 8);     /* Set high byte of divisor */
}
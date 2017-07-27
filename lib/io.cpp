#include <stdint.h>

uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void outb(uint16_t port, uint8_t val) {
    asm ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

void io_wait() {
    asm ( "outb %%al, $0x80" : : "a"(0) );
}

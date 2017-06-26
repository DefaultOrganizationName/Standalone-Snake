#include <keyboard_communicator.h>

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

static int getScancode()
{
	int c = 0;
	for (;;) {
		if (inb(0x60) != c)	{
			c = inb(0x60);
			if (c > 0) return c;
		}
	}
}

static int getchar()
{
	return getScancode() + 1;
}

int get_pressed_button() {
	return getchar();
}
#include <keyboard_communicator.h>
#include <types.h>

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static int get_scan_code() {
	int c = 0;
	for (;;) {
		if (inb(0x60) != c)	{
			c = inb(0x60);
			if (c > 0) return c;
		}
	}
}

static char codes[300];

char get_pressed_button() {
	static int codes_got = 0;
	if (codes_got == 0) {
		codes_got = 1;
		for (int i = 0; i < 300; i++) codes[i] = 0;
		codes[0x1e] = 'a';
		codes[0x1f] = 's';
		codes[0x20] = 'd';
		codes[0x11] = 'w';
	}
	return codes[get_scan_code()];

}
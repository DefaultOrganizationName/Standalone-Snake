#include <keyboard_communicator.h>
#include <types.h>

const uint16_t IO_PORT = 0x60;

static inline uint8_t inb() {
    uint8_t ret;
    asm ("inb %1, %0" : "=a"(ret) : "Nd"(IO_PORT));
    return ret;
}

static int get_scan_code() {
	int c = 0;
	for (;;) {
		if (inb() != c)	{
			c = inb();
			if (c > 0) return c;
		}
	}
}

static char codes[300];

static void codes_memoization() {
	static int codes_got = 0;
	if (codes_got == 0) {
		codes_got = 1;
		for (int i = 0; i < 300; i++) codes[i] = 0;
		codes[0x1e] = 'a';
		codes[0x1f] = 's';
		codes[0x20] = 'd';
		codes[0x11] = 'w';
		codes[0x13] = 'r';
	}	
}

char get_pressed_button() {
	codes_memoization();
	return codes[get_scan_code()];
}

char check_io_port() {
	int code = inb();
	return code > 0 ? codes[code] : 0;
}
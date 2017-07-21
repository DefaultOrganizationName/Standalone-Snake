#include "screen.h"
#include "easy_printf.h"

extern "C" int fun() {
	clear_screen();
	printf("\nloool\n");
	int a = 0;
	while(a < 4e7) {
		a += 1;
	}
	return a;
}
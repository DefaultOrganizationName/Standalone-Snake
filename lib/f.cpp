#include "screen.h"
#include "easy_printf.h"

struct alpha {
	int a, b;
	alpha (int a, int b) : a(a), b(b) {}
	alpha () {}
};

extern "C" int fun() {
	clear_screen();
	printf("\nloool\n");
	alpha omg = {.a = 1, .b = 2};
	if (omg.a == 1 && omg.b == 2) {
		printf("OMG I GOT IT, YEAH BAAABY I GOT IT!");
	}

	int a = 0;
	while(a < 4e7) {
		a += 1;
	}
	return a;
}
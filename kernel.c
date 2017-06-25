#include "printf.h"
#include "screen.h"
#include "types.h"

#include "standalone_snake_game.h"

// const int N = 10;

// unsigned int DEF_IO_BASE = 0x60;
// unsigned int DEF_IO_BASE1 = 0x64;
// unsigned int X = 0x20;

// unsigned char inportb(unsigned int port)
// {
//    unsigned char ret;
//    asm volatile ("inb %%dx,%%al":"=a" (ret):"d" (port));
//    return ret;
// }

void main(void) {
	clear_screen();

	start_snake();

	// int *b = DEF_IO_BASE1;
	// int *a= DEF_IO_BASE;
	// int base_v = 0;

	// printf("%x\n", *a);printf("%x\n", *b);
	// //*b = 0x20; *b = 0xaa;
	// printf("%x\n", *a);printf("%x\n", *b);

	// *a = X;

	// unsigned int prev = 0;
	// while (1 == 1)
	// {
	// 	if (*b != prev) {
	// 		printf("%d\n", *b);	
	// 		prev = *b;
	// 	}
	// }

	// printf("\n>>> Hello World!\n");
	// while (1 == 1) for (int i = 0; i < N; i++) printf("%d", i);

}

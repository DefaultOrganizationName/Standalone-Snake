#include "lib/standalone_snake_game.h"
#include "lib/keyboard_communicator.h"

extern "C" int kernel_main() {

	// GDT[0] = {.base=0, .limit=0, .type=0};                     // Selector 0x00 cannot be used
	// GDT[1] = {.base=0, .limit=0xffffffff, .type=0x9A};         // Selector 0x08 will be our code
	// GDT[2] = {.base=0, .limit=0xffffffff, .type=0x92};         // Selector 0x10 will be our data

	keyboard_init();

	clear_screen();
	snake_menu();
	clear_screen();

	do {
		start_snake();
		show_points();
	} while (restart_option());

	return 0;
}

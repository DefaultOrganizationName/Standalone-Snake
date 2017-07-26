#include "lib/standalone_snake_game.h"
#include "lib/keyboard_communicator.h"
#include "lib/easy_printf.h"

extern "C" int kernel_main() {

	keyboard_init();

	clear_screen();
	
	int a = 0;
	while (true) {}

	snake_menu();
	clear_screen();

	do {
		start_snake();
		show_points();
	} while (restart_option());

	return 0;
}

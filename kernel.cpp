#include "lib/standalone_snake_game.h"
#include "lib/keyboard_communicator.h"
#include "lib/pit.h"
#include "lib/easy_printf.h"
#include "lib/time.h"

extern "C" int kernel_main() {

	keyboard_init();
	init_pit(1500);	

	clear_screen();

	snake_menu();
	clear_screen();

	do {
		start_snake();
		show_points();
	} while (restart_option());

	return 0;
}

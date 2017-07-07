#include <standalone_snake_game.h>
#include <keyboard_communicator.h>

int main(void) {
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

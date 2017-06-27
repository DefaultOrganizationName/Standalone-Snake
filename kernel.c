#include <types.h>
#include <standalone_snake_game.h>
#include <keyboard_communicator.h>

int main(void) {
	clear_screen();
	keyboard_init();
	snake_menu();
	clear_screen();
	int restart = 1;
	while (restart) {
		start_snake();
		show_points();
		restart = restart_option();
	}
	return 0;
}

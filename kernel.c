#include "screen.h"
#include "types.h"

#include "standalone_snake_game.h"

int main(void) {

	clear_screen();
	int restart = 1;
	while (restart) {
		start_snake();
		show_points();
		restart = restart_option();
	}


	return 0;
}

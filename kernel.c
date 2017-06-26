#include "screen.h"
#include "types.h"

#include "standalone_snake_game.h"

int main(void) {

	clear_screen();
	start_snake();
	show_points();

	return 0;
}

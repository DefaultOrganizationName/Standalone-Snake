#include "printf.h"
#include "screen.h"
#include "types.h"

#include "standalone_snake_game.h"

void main(void) {
	clear_screen();

	start_snake();
	// char prev = 0;
	// while (1) {
	// 	char c = get_pressed_button();
	// 	if (c != prev) {
	// 		printf("%c", c);
	// 		prev = c;
	// 	}
	// }

	// int a = 0x1e;
	// printf("%d", a);

}

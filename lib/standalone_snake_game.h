#ifndef STANDALONE_SNAKE_H
#define STANDALONE_SNAKE_H

#include "screen.h"

namespace game {
	void start_snake();
	void on_key_pressed(char);
	void show_points();
	int restart_option();
	void snake_menu();
}

#endif
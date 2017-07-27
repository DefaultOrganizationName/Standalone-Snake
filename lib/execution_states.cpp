#include "execution_states.h"

static state_t cur_state = START;

static char button = 0;

state_t get_state() {
	return cur_state;
}

void update_state(state_t to) {
	cur_state = to;
}

void update_checker(char new_button) {
	button = new_button;
}

bool check_key_pressed (char b) {
	return button == b;
} 

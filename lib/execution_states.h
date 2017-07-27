#ifndef _EXECUTION_STATES_H
#define _EXECUTION_STATES_H

enum state_t {
	START, GAME, WAIT_FOR_BUTTON, FINISH
};

state_t get_state();
void update_state(state_t);
void update_checker(char);
bool check_key_pressed(char);

#endif
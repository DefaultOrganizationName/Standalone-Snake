#include "time.h"
#include "execution_states.h"

uint64_t sec_count = 0;

uint64_t get_sec_count() {
	return sec_count;
}

void sleep(uint64_t secs) {
	uint64_t t1 = get_sec_count();
	uint64_t t2 = t1 + secs;
	while (sec_count < t2) {
		asm ("hlt");
	}
}

void inc_time() {
	sec_count++;
}

void wait_for_button_press(char button) {
	update_state(WAIT_FOR_BUTTON);
	update_checker(button);
	while (get_state() != GAME) {
		asm ("hlt");
	}
}

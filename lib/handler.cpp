#include "easy_printf.h"
#include "keyboard_communicator.h"
#include "pic.h"
#include "time.h"
#include "execution_states.h"
#include "standalone_snake_game.h"

extern "C" void on_key_pressed() {

	char pressed = get_pressed_button();
	switch (get_state()) {
		case GAME:
			game::on_key_pressed(pressed);
			break;
		case WAIT_FOR_BUTTON:
			if (check_key_pressed(pressed)) {
				update_state(GAME);
			}
			break;
		default:
			break;
	}
	pic_send_eoi(0x1);
}

extern "C" void on_timer_ticked() {
	static int t = 0;
	if (t == 20) {
		inc_time();
		t = 0;
	}
	t++;
	pic_send_eoi(0x0);
}

extern "C" void ignore() {
	pic_send_eoi(0x0);
}
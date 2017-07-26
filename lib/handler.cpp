#include "easy_printf.h"
#include "keyboard_communicator.h"
#include "pic.h"
#include "time.h"

extern "C" void on_key_pressed() {
	get_pressed_button();
	printf("lol");
	pic_send_eoi(0x1);
}

extern "C" void on_timer_ticked() {
	static int t = 0;
	if (t == 19) {
		inc_time();
		t = 0;
	}
	t++;
	pic_send_eoi(0x0);
}

extern "C" void ignore() {
	pic_send_eoi(0x0);
}
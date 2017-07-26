#include "easy_printf.h"
#include "keyboard_communicator.h"
#include "pic.h"

extern "C" void on_key_pressed() {
	char pressed = get_pressed_button();
	printf("lol");
	pic_send_eoi(0x1);
}

extern "C" void ignore() {
	pic_send_eoi(0x0);
}
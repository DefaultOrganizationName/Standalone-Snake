#ifndef KEY_BOARD_COMMUNICATOR
#define KEY_BOARD_COMMUNICATOR

// *
 / Function to get one of 4 buttons that is pressed on the keyboard.
 / Returns 'a' if 'a' is pressed
 / Returns 'w' if 'w' is pressed
 / Returns 's' if 's' is pressed
 / Returns 'd' if 'd' is pressed
 / Returns 0 if no one of this buttons is pressed.
*/
char get_pressed_button();

#endif
#ifndef _SCREEN_H
#define _SCREEN_H

#include <stddef.h>
#include <stdint.h>
#include "screen_constants.h"

void clear_screen();
void fast_clear_screen();
void putchar( int c );
void putchar_cl(int, int);
void putchar_coord(char, uint8_t, uint8_t);

#endif
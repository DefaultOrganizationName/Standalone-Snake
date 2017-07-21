#ifndef _SCREEN_H
#define _SCREEN_H

#include <stddef.h>
#include <stdint.h>
#include "screen_constants.h"

void clear_screen();
void fast_clear_screen();
void putchar( int c );
void putchar_cl(int, int);

#endif
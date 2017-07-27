#ifndef _EASY_PRINTF_H
#define _EASY_PRINTF_H
#include <stddef.h>
#include "screen.h"

size_t strlen(const char* s);

void printf(const char* s);

void printf(const char* s, int color);

void printf(const int number);

#endif
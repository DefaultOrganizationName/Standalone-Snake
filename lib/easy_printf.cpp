#include "easy_printf.h"


size_t strlen(const char* s) {
	size_t i = 0;
	while (s[i]) i++;
	return i;
}

void printf(const char* s) {
	for (size_t i = 0; i < strlen(s); i++) putchar(s[i]);
}

void printf(const char* s, int color) {
	for (size_t i = 0; i < strlen(s); i++) putchar_cl(s[i], color);
}
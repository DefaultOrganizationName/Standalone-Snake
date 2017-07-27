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

void printf(const int number) {
	static int prev_number = -1;
	if (prev_number == number) return;
	prev_number = number;
	int p = number;
	static int arr[10];
	int len = 0;
	while (p > 0) {
		arr[len++] = p % 10;
		p /= 10;
	}
	for (int i = len - 1; i >= 0; i--) {
		char c = arr[i] + '0';
		putchar(c);
	}
	if (len == 0) putchar('0');
}

#ifndef _TIME_H
#define _TIME_H

#include <stdint.h>

void inc_time();
void sleep(uint64_t secs);
uint64_t get_sec_count();

#endif
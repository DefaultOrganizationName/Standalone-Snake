#ifndef _QUEUE_H
#define _QUEUE_H

#include <stddef.h>
#include <stdint.h>

void queue_init();
void queue_push(int val);
int queue_pop();
size_t get_size(); 

#endif
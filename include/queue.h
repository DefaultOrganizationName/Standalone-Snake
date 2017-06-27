#ifndef _QUEUE_H
#define _QUEUE_H

#include <types.h>

#define MAXQUEUEVALUE 10

void queue_init();
void queue_push(int val);
int queue_pop();
size_t get_size(); 

#endif
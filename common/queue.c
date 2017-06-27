#include <queue.h>

int data[MAXQUEUEVALUE];
int first;
size_t size;

void queue_init()
{
    first = -1;
    size = 0;
}

void queue_push(int val) 
{
    int position;
    if (first == -1) 
    {
        first = position = 0;
    } else {
        position = (first + size) % MAXQUEUEVALUE;
    }
    if (size == MAXQUEUEVALUE) 
    {
        first = (first + 1) % MAXQUEUEVALUE;
    } else {
        size++;
    }
    data[position] = val;
}

int queue_pop() 
{
    if (size == 0) return 0;
    size--;
    int old_first = data[first];
    // data[first] = 0;
    first = (first + 1) % MAXQUEUEVALUE;
    
    return old_first;
}

size_t get_size() {
    return size;
}
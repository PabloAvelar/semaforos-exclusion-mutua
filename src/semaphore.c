//
// Created by Avelar on 10/24/2024.
//

#include "../include/semaphore.h"
#include "../include/queue.h"

struct Queue* queue;
void wait(struct Semaphore* s) {
    s->counter --;
    if (s->counter < 0) {
    }
}

void signal(struct Semaphore* s);

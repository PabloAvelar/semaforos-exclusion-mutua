//
// Created by Avelar on 10/24/2024.
//

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "../src/queue.c"

struct Semaphore {
    int counter;
    struct Queue* blocked;
};

void wait(struct Semaphore* s);

void signal(struct Semaphore* s);

#endif //SEMAPHORE_H

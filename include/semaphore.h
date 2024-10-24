//
// Created by Avelar on 10/24/2024.
//

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "../src/queue.c"

struct Semaphore {
    int counter;
    struct queue;
};

#endif //SEMAPHORE_H

//
// Created by Avelar on 10/24/2024.
//

#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>
#include <stdio.h>

#include "Node.h"

struct Queue {
    struct Node* front;
    struct Node* last;
};

// Inicializar
void initQueue(struct Queue* queue);

// Encolar
void enqueue(struct Queue* queue, int value);

// Desencolar
int dequeue(struct Queue* queue);

// Verifica si esta vacia
bool isEmpty(struct Queue* queue);

// Liberar memoria utilizada por la cola
void freeQueue(struct Queue* queue);

// Mostrando la cola
void showQueue(struct Queue* queue);

#endif //QUEUE_H

//
// Created by Avelar on 10/24/2024.
//

#include "../include/queue.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Verifica si esta vacia
bool isEmpty(struct Queue *queue) {
    return queue->front == NULL;
}

// Inicializar
void initQueue(struct Queue *queue) {
    queue->front = NULL;
    queue->last = NULL;
}

// Encolar
void enqueue(struct Queue *queue, int value) {
    struct Node *newNode = (struct Node *) malloc((sizeof(struct Node)));
    if (!newNode) {
        perror("Error al asignar memoria.");
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = queue->last;

    // Comprobando encolar en cola vacia
    if (isEmpty(queue)) {
        queue->front = newNode;
    } else {
        queue->last->next = newNode;
    }

    queue->last = newNode;
}

// Desencolar
int dequeue(struct Queue *queue) {
    // Checando que la cola no esté vacía para hacer esto
    if (isEmpty(queue)) {
        perror("La cola esta vacia");
        exit(EXIT_FAILURE);
    }

    struct Node *temp = queue->front;
    const int value = temp->value;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->last = NULL;
    } else {
        queue->front->prev = NULL;
    }

    free(temp);
    return value;
}

// Liberar memoria utilizada por la cola
void freeQueue(struct Queue *queue) {
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
}

// Mostrando la cola
void showQueue(struct Queue *queue) {
    struct Node *p = queue->front;
    if (isEmpty(queue)) {
        printf("Cola vacia");
        return;
    }

    while (p) {
        printf("%i -> ", p->value);
        p = p->next;
    }
    printf("\n\a");
}

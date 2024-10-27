//
// Created by Avelar on 10/25/2024.
//

#include "../include/buffer.h"

#include <stdio.h>

int buffer[BUFFER_SIZE];
int count = 0;
int producer_count = 0;
int consumer_count = 0;

HANDLE mutex;
HANDLE empty;
HANDLE full;

void initialize_sync() {
    // Mutex para exclusión mutua en la sección crítica
    mutex = CreateMutex(NULL, FALSE, NULL);

    // Semáforo `empty` inicializado a `BUFFER_SIZE` para indicar espacios vacíos
    empty = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);

    // Semáforo `full` inicializado a 0 porque el buffer empieza vacío
    full = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);
}
void show_buffer() {
    printf("[");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("%d%s", buffer[i], (i == BUFFER_SIZE - 1) ? "" : ",");
    }
    printf("]\n");
}

void cleanup_sync() {
    CloseHandle(mutex);
    CloseHandle(empty);
    CloseHandle(full);
}

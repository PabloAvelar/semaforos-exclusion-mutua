//
// Created by Avelar on 10/25/2024.
//

#include "../include/buffer.h"

#include <stdio.h>

int buffer[BUFFER_SIZE];
int count = 0;

HANDLE mutex;
HANDLE empty;
HANDLE full;

void initialize_sync() {
    mutex = CreateMutex(NULL, FALSE, NULL);
    empty = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);
    full = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);
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
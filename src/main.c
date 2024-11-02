#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "../include/buffer.h"
#include "../include/consumer.h"
#include "../include/producer.h"

#define THREADCOUNT 3 //Hilo extra de control para alternar entre consumidor y productor nuv

HANDLE sem_producer;
HANDLE sem_consumer;

// Hilo de control que alterna de forma random entre productor y consumidor
DWORD WINAPI control_thread(LPVOID param) {
    while (1) {
        int turn = rand() % 2; // Escoge aleatoria entre productor y consumidor
        if (turn == 0) {
            ReleaseSemaphore(sem_producer, 1, NULL); 
        } else {
            ReleaseSemaphore(sem_consumer, 1, NULL); 
        }
        Sleep(500);
    }
}


int main(void) {
    srand((unsigned int)time(NULL)); // Inicializar semilla de aleatoriedad

    // Inician los semáforos y sincronización
    initialize_sync();
    sem_producer = CreateSemaphore(NULL, 0, 1, NULL);
    sem_consumer = CreateSemaphore(NULL, 0, 1, NULL);

    // Creando hilos
    HANDLE threads[THREADCOUNT];
    threads[0] = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    threads[1] = CreateThread(NULL, 0, consumer, NULL, 0, NULL);
    threads[2] = CreateThread(NULL, 0, control_thread, NULL, 0, NULL);

    WaitForMultipleObjects(THREADCOUNT, threads, TRUE, INFINITE);

    // Limpia recursos
    CloseHandle(sem_producer);
    CloseHandle(sem_consumer);
    cleanup_sync();

    return 0;
}

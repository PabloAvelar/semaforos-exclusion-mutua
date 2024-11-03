//
// Created by Avelar on 10/25/2024.
//

#include "../include/producer.h"

#include <stdio.h>

#include "../include/buffer.h"

extern HANDLE sem_producer;
extern HANDLE sem_consumer;
DWORD WINAPI producer(LPVOID param) {
    int item = 0;
    int randomSleep = 0;
    int turn_count = 0;

    while (1) {
        WaitForSingleObject(sem_producer, INFINITE); // Espera su turno
        item = rand() % 100 + 1;

        WaitForSingleObject(empty, INFINITE); // Espera si el buffer está lleno!
        WaitForSingleObject(mutex, INFINITE); // Espera a la sección crítica!

        // Entra a la sección crítica después de esperar
        buffer[producer_count % BUFFER_SIZE] = item;
        producer_count++;
        count++; // conteo de elementos del buffer

        printf("\033[0;33m[Productor]\033[0m: trabajando\n");
        printf("\033[0;33m[Productor]\033[0m: produce %d\n", item);

        // Mostrando el buffer
        show_buffer();

        // Sale de la sección crítica!
        ReleaseMutex(mutex);
        turn_count++;

        // Notifica que hay un item nuevo!
        ReleaseSemaphore(full, 1, NULL);

        /*if (turn_count == 3 || count == BUFFER_SIZE) {
            turn_count = 0;
        }*/

        // Durmiendo el proceso de forma aleatoria para que los procesos tomen el CPU al azar
        // randomSleep = rand() % (3000 - 1000 + 1) + 1000;
        randomSleep = rand() % 2000 + 800; // Tiempo de espera aleatorio entre800 y 2500 ms
        printf("\033[0;33m[Productor]\033[0m: durmiendo por %d segundos\n", randomSleep);
        printf("\n----------------------------------\n");
        Sleep(randomSleep);
    }
}
//
// Created by Avelar on 10/25/2024.
//

#include "../include/producer.h"

#include <stdio.h>

#include "../include/buffer.h"

DWORD WINAPI producer(LPVOID param) {
    int item = 0;
    int randomSleep = 0;
    int turn_count = 0;

    while (1) {
        item = rand() % 100 + 1;
        /*printf("\n");
        if (count == BUFFER_SIZE) {
            printf("BUFFER LLENO\n");
        }*/

        WaitForSingleObject(empty, INFINITE); // Espera si el buffer está lleno!
        WaitForSingleObject(mutex, INFINITE); // Espera a la sección crítica!

        // Entra a la sección crítica después de esperar
        printf("Espacio asignado: %d\n", producer_count % BUFFER_SIZE);
        buffer[producer_count % BUFFER_SIZE] = item;
        producer_count++;
        count++; // conteo de elementos del buffer

        printf("[Productor]: trabajando\n");
        printf("[Productor]: produce %d\n", item);

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
        randomSleep = 2000;
        printf("[Productor]: durmiendo por %d segundos\n", randomSleep);
        Sleep(randomSleep);
    }
}

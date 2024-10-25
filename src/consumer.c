//
// Created by Avelar on 10/25/2024.
//

#include "../include/consumer.h"

#include <stdio.h>

#include "../include/buffer.h"

DWORD WINAPI consumer(LPVOID param) {
    int item = 0;
    int randomSleep = 0;

    while (1) {
        WaitForSingleObject(empty, INFINITE); // Espera si el buffer está vacío!
        WaitForSingleObject(mutex, INFINITE); // Espera la sección crítica!

        // Entra a la sección crítica
        printf("\n[Consumidor]: Trabajando\n");
        item = buffer[--count];
        buffer[count] = 0;
        printf("[Consumidor]: consume %d\n", item);

        // Mostrando buffer
        show_buffer();

        // Se hace wey un rato para que se vea el buffer
        Sleep(1500);

        // Levantando los semáforos
        ReleaseMutex(mutex); // Sale de la sección crítica!
        ReleaseSemaphore(full, 1, NULL); // Notifica que hay un espacio disponible!

        // Durmiendo el proceso de forma aleatoria para que los procesos tomen el CPU al azar
        randomSleep = rand() % (3000 - 1000+1) + 1000;
        printf("[Consumidor]: durmiendo por %d segundos\n", randomSleep);
        Sleep(randomSleep);
    }
}

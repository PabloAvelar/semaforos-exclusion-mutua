//
// Created by Avelar on 10/25/2024.
//

#include "../include/producer.h"

#include <stdio.h>

#include "../include/buffer.h"

DWORD WINAPI producer(LPVOID param) {
    int item = 0;
    int randomSleep = 0;

    while (1) {
        item = rand() % 100 + 1;
        WaitForSingleObject(full, INFINITE); // Espera si el buffer está lleno!
        WaitForSingleObject(mutex, INFINITE); // Espera a la sección crítica!

        // Entra a la sección crítica después de esperar
        buffer[count++] = item;
        printf("\n[Productor]: trabajando\n");
        printf("[Productor]: produce %d\n", item);

        // Mostrando el buffer
        show_buffer();

        // Se hace wey un rato nomas para que se vea
        Sleep(1500);

        ReleaseMutex(mutex); // Sale de la sección crítica!
        ReleaseSemaphore(empty, 1, NULL); // Notifica que hay un item nuevo!

        // Durmiendo el proceso de forma aleatoria para que los procesos tomen el CPU al azar
        randomSleep = rand() % (3000 - 1000+1) + 1000;
        printf("[Productor]: durmiendo por %d segundos\n", randomSleep);
        Sleep(randomSleep);
    }
}

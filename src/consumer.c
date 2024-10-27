//
// Created by Avelar on 10/25/2024.
//

#include "../include/consumer.h"

#include <stdio.h>

#include "../include/buffer.h"

DWORD WINAPI consumer(LPVOID param) {
    int item = 0;
    int randomSleep = 0;
    int turn_count = 0;

    while (1) {
        /*printf("\n");
        if (count == 0) {
            printf("BUFFER VACIO\n");
        }*/
        WaitForSingleObject(full, INFINITE); // Espera si el buffer está vacío!
        WaitForSingleObject(mutex, INFINITE); // Espera la sección crítica!

        // Entra a la sección crítica
        printf("[Consumidor]: Trabajando\n");
        item = buffer[consumer_count % BUFFER_SIZE];
        buffer[consumer_count % BUFFER_SIZE] = 0; // Limpia la posición después de consumir
        consumer_count++;

        count--; // Decrementando conteo de elementos del buffer
        printf("[Consumidor]: consume %d\n", item);

        // Mostrando buffer
        show_buffer();

        // Levantando los semáforos
        ReleaseMutex(mutex); // Sale de la sección crítica!
        turn_count++;
        ReleaseSemaphore(empty, 1, NULL); // Notifica que hay un espacio disponible!
        /*if (turn_count == 3) {
            turn_count = 0;
        }*/

        // Durmiendo el proceso de forma aleatoria para que los procesos tomen el CPU al azar
        //randomSleep = rand() % (3000 - 1000 + 1) + 1000;
        randomSleep = 2000;
        printf("[Consumidor]: durmiendo por %d segundos\n", randomSleep);
        Sleep(randomSleep);
    }
}

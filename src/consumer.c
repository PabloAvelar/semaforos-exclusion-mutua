//
// Created by Avelar on 10/25/2024.
//

#include "../include/consumer.h"

#include <stdio.h>

#include "../include/buffer.h"
extern HANDLE sem_producer;
extern HANDLE sem_consumer;
DWORD WINAPI consumer(LPVOID param) {
    int item = 0;
    int randomSleep = 0;
    int turn_count = 0;
    int head = 0;
    while (1) {
         WaitForSingleObject(sem_consumer, INFINITE); // Espera su turno
        /*printf("\n");
        if (count == 0) {
            printf("BUFFER VACIO\n");
        }*/
        WaitForSingleObject(full, INFINITE); // Espera si el buffer está vacío!
        WaitForSingleObject(mutex, INFINITE); // Espera la sección crítica!

        // Entra a la sección crítica
        printf("[Consumidor]: Trabajando\n");
        item = buffer[head];
        buffer[head] = 0;
        head = (head + 1) % BUFFER_SIZE; // Avanza el índice de la cabeza de la cola


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
        randomSleep = rand() % 2000 + 800; // Tiempo de espera aleatorio entre 800 y 2500 ms
        printf("[Consumidor]: durmiendo por %d segundos\n", randomSleep);
        Sleep(randomSleep);
    }
}

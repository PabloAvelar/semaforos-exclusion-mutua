#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include "../include/buffer.h"
#include "../include/consumer.h"
#include "../include/producer.h"

#define THREADCOUNT 2

int main(void) {
    // Inicializando semáforos
    initialize_sync();

    // Creando hilos
    HANDLE threads[THREADCOUNT];
    threads[0] = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    threads[1] = CreateThread(NULL, 0, consumer, NULL, 0, NULL);

    // WaitForMultipleObjects(THREADCOUNT, threads, TRUE, INFINITE);
    while (1) {
        int randomTurn = rand() % 2;

        if (randomTurn == 0) {
            // Permitir al productor
            WaitForSingleObject(threads[0], 0); // Verifica si el productor está listo
        } else {
            // Permitir al consumidor
            WaitForSingleObject(threads[1], 0); // Verifica si el consumidor está listo
        }

        // Se hace wey un rato para decidir de nuevo
        Sleep(500);
    }

    cleanup_sync();

    return 0;
}

/*
DWORD WINAPI tarea(LPVOID param) {
    int thread_id = *(int *) param; // Convierte el parámetro recibido
    printf("\n[Thread %d] Iniciando la tarea\n", thread_id);

    DWORD dwWaitResult = WaitForSingleObject(
        s,
        INFINITE
    );

    if (dwWaitResult == WAIT_OBJECT_0) {
        // Intentando entrar


        system("cls");

        // Mostrando el arreglo
        printf("\t[");
        for(int i = 0; i < BUFFER_SIZE; i++) {
            printf("%d, ", shared_resource[i]);
        }
        printf("]\n");

        printf("Thread %d: su espera tuvo exito\n", GetCurrentThreadId());

        // Sección crítica
        shared_resource[resource_counter] = ++resource_counter;
        printf("[Thread %d] Recurso compartido modificado %d\n", thread_id);
        Sleep(2000);

        // Liberar el semáforo
        if (!ReleaseSemaphore(s, 1, NULL)) {
            printf("[Thread %d] Error al liberar el semáforo: %d\n", thread_id, GetLastError());
        } else {
            printf("[Thread %d] Semaforo liberado\n", thread_id);
        }
    } else {
        printf("[Thread %d] Error al intentar adquirir el semáforo\n", thread_id);
    }

    printf("[Thread %d] Tarea finalizada\n", thread_id);


    return 0;
}
*/

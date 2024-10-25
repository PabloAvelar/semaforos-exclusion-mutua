#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

//#include "../include/queue.h"

DWORD WINAPI tarea(LPVOID param) {
    int thread_id = *(int*)param; // Convierte el parámetro recibido
    printf("Soy un hilo ejecutando la tarea: %d\n", thread_id);

    return 0;
}

/*void testqueue() {
    struct Queue queue;
    initQueue(&queue);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    enqueue(&queue, 40);

    printf("Mostrando cola:\n");
    showQueue(&queue);

    printf("Desencolando:\n");
    dequeue(&queue);
    showQueue(&queue);

    printf("Limpiando la cola:\n");
    freeQueue(&queue);
    showQueue(&queue);

}*/

int main() {
    const int NUM_THREADS = 5;
    HANDLE threads[NUM_THREADS];
    int threads_ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        threads_ids[i] = i;

        // Creando el nuevo hilo
        threads[i] = CreateThread(
            NULL, // atributos de seguridad, usando el predeterminado
            0,     // Tamaño de la pila
            tarea, //Función a ejecutar el hilo
            &threads_ids[i], // Parámetro para la función del hilo
            0, // Bandera de creación, 0 para ejecución inmediata.
            NULL // ID del hilo, NULL porque no se necesita.

            );

        if (threads[i] == NULL) {
            printf("Error al crear el hilo %d\n", i);
        }
    }

    WaitForMultipleObjects(NUM_THREADS, threads, TRUE, INFINITE);

    // Cerrando los handles de los hilos
    for(int i = 0; i < NUM_THREADS; i++) {
        CloseHandle(threads[i]);
    }

    printf("Todos los hilos han terminado.\a\n");
    system("pause");
    return 0;
}

#include <stdio.h>
//#include <pthread.h>
#include <stdlib.h>

#include "../include/queue.h"

void* tarea(void* arg) {
    printf("Soy un hilo ejecutando la tarea: %ld\n", (long)arg);

    return NULL;
}

/*void multiprogramming() {
    pthread_t thread1, thread2;

    // Se crean dos hilos!!
    pthread_create(&thread1, NULL, tarea, (void*)1);
    pthread_create(&thread2, NULL, tarea, (void*)2);

    // Se espera a que terminen
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Todos los hilos han terminado.");
}*/

void testqueue() {
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

}

int main() {

    testqueue();
    printf("\a");
    system("pause");
    return 0;
}

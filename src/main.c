#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

#define MAX_SEM_COUNT 10
#define THREADCOUNT 5
#define BUFFER_SIZE 10

HANDLE s;

DWORD WINAPI tarea(LPVOID param);

int shared_resource[BUFFER_SIZE];
int resource_counter = 0;

int main(void) {
    HANDLE threads[THREADCOUNT];
    int threads_ids[MAX_SEM_COUNT];
    DWORD ThreadID;

    // Se crea un semáforo con un conteo máximo de MAX_SEM_COUNT
    s = CreateSemaphore(
        NULL,
        1,
        1,
        NULL
    );

    if (!s) {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return EXIT_FAILURE;
    }

    // Creando hilos
    for (int i = 0; i < THREADCOUNT; i++) {
        threads_ids[i] = i;
        threads[i] = CreateThread(
            NULL,
            0,
            tarea,
            &threads_ids[i],
            0,
            &ThreadID
        );

        if (!threads[i]) {
            printf("CreateThread error: %d\n", GetLastError());
            return EXIT_FAILURE;
        }
    }

    WaitForMultipleObjects(THREADCOUNT, threads, TRUE, INFINITE);
    for (int i = 0; i < THREADCOUNT; i++) {
        CloseHandle(threads[i]);
    }

    CloseHandle(s);

    printf("Todos los hilos han terminado.\a\n");
    printf("Resultado final: [");
    for(int i = 0; i < BUFFER_SIZE; i++) {
        printf("%d, ", shared_resource[i]);
    }
    printf("]\n");
    system("pause");
    return 0;
}

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

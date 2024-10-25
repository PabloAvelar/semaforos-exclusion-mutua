#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

#define MAX_SEM_COUNT 10
#define THREADCOUNT 5

HANDLE s;
DWORD WINAPI tarea(LPVOID param);
int shared_resource = 0;
int main(void) {
    HANDLE threads[THREADCOUNT];
    int threads_ids[MAX_SEM_COUNT];
    DWORD ThreadID;

    // Se crea un semáforo con un conteo máximo de MAX_SEM_COUNT
    s = CreateSemaphore(
        NULL,
        MAX_SEM_COUNT,
        MAX_SEM_COUNT,
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
    for(int i = 0; i < THREADCOUNT; i++) {
        CloseHandle(threads[i]);
    }

    CloseHandle(s);

    printf("Todos los hilos han terminado.\a\n");
    system("pause");
    return 0;
}

DWORD WINAPI tarea(LPVOID param) {
    int thread_id = *(int *) param; // Convierte el parámetro recibido
    printf("Soy un hilo ejecutando la tarea: %d\n", thread_id);

    DWORD dwWaitResult;
    BOOL bContinue = TRUE;

    while(bContinue) {
        // Intentando entrar
        dwWaitResult = WaitForSingleObject(
            s,
            5000
            );
        switch (dwWaitResult) {
            // Si se lanzó un Signal
            case WAIT_OBJECT_0:
                printf("Thread %d: wait succeded\n", GetCurrentThreadId());
                bContinue=FALSE;
                // Simulando tiempo de tarea
                Sleep(3000);

            // Soltado el semáforo cuando termina la tarea
            if (!ReleaseSemaphore(
                s,
                1, // Incremento del contador
                NULL
                )) {
                printf("ReleaseSemaphore error: %d\n", GetLastError());
            }
            break;

            // Si el semáforo no recibió un Signal, entonces ocurre un tiempo de espera
            case WAIT_TIMEOUT:
                printf("Thread %d: wait timed out\n", GetCurrentThreadId());
            break;
        }
    }

    return TRUE;
}

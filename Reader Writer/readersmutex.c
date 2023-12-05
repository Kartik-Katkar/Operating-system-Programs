#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#define sleep_ms(ms) Sleep(ms)
#else
#include <unistd.h>
#define sleep_ms(ms) usleep((ms) * 1000)
#endif

pthread_mutex_t x, wsem;
pthread_t tid;
int readcount;

void initialize() {
    pthread_mutex_init(&x, NULL);
    pthread_mutex_init(&wsem, NULL);
    readcount = 0;
}

void *reader(void *param) {
    int waittime;
    waittime = rand() % 5;
    pthread_t tid = pthread_self();
    printf("\nReader with thread id: %lu is trying to enter", tid);
    pthread_mutex_lock(&x);
    readcount++;
    if (readcount == 1)
        pthread_mutex_lock(&wsem);
    printf("\nReader with thread id: %lu is inside (%d readers)", tid, readcount);
    pthread_mutex_unlock(&x);

    sleep_ms(waittime * 1000); // Sleep in milliseconds

    pthread_mutex_lock(&x);
    readcount--;
    if (readcount == 0)
        pthread_mutex_unlock(&wsem);
    pthread_mutex_unlock(&x);
    printf("\nReader with thread id: %lu has left", tid);
    return NULL;
}

void *writer(void *param) {
    int waittime;
    waittime = rand() % 2; // Reduce the sleep time for writers
    pthread_t tid = pthread_self();
    printf("\nWriter with thread id: %lu is trying to enter", tid);
    pthread_mutex_lock(&wsem);
    printf("\nWriter with thread id: %lu has entered", tid);

    sleep_ms(waittime * 1000); // Sleep in milliseconds

    pthread_mutex_unlock(&wsem);
    printf("\nWriter with thread id: %lu has left", tid);
    sleep_ms(30000); // Sleep for 30 seconds
    exit(0);
}

int main() {
    int n1, n2, i;
    printf("\n----------------------------- ");
    printf("\nInput the number of readers: ");
    scanf("%d", &n1);
    printf("\nInput the number of writers: ");
  
    scanf("%d", &n2);
    printf("\n----------------------------- ");

    // Initialize the mutexes
    initialize();

    for (i = 0; i < n1; i++)
        pthread_create(&tid, NULL, reader, NULL);
    for (i = 0; i < n2; i++)
        pthread_create(&tid, NULL, writer, NULL);

    // Sleep for 30 seconds to allow threads to run
    sleep_ms(30000);

    // Cancel the threads to exit the infinite loops
    pthread_cancel(tid);

    // Wait for all threads to finish
    pthread_join(tid, NULL);

    // Clean up mutexes
    pthread_mutex_destroy(&x);
    pthread_mutex_destroy(&wsem);

    return 0;
}
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define MaxItems 5 // Maximum items a producer can produce or a consumer can consume
#define BufferSize 5 // Size of the buffer

int buffer[BufferSize];
int in = 0;
int out = 0;
sem_t empty; // Semaphore to track empty slots in the buffer
sem_t full;  // Semaphore to track filled slots in the buffer

void *producer(void *pno)
{
    int item;
    for (int i = 0; i < MaxItems; i++) {
        item = rand(); // Produce a random item

        // Wait for an empty slot in the buffer
        sem_wait(&empty);

        // Critical section: Add item to the buffer
        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pno), buffer[in], in);
        in = (in + 1) % BufferSize;

        // Signal that a slot is now filled
        sem_post(&full);

        // Check if the buffer is full
        if (in == out) {
            printf("Buffer is full\n");
        }
    }
}

void *consumer(void *cno)
{
    int item;
    for (int i = 0; i < MaxItems; i++) {

        // Check if the buffer is empty
        if (in == out) {
            printf("Buffer is empty\n");
        }

        // Wait for a filled slot in the buffer
        sem_wait(&full);

        // Critical section: Remove item from the buffer
        item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n", *((int *)cno), item, out);
        out = (out + 1) % BufferSize;

        // Signal that a slot is now empty
        sem_post(&empty);
    }
}

int main()
{
    pthread_t pro[5], con[5];
    sem_init(&empty, 0, BufferSize); // Initialize empty semaphore with buffer size
    sem_init(&full, 0, 0);           // Initialize full semaphore with 0 items in the buffer

    int a[5] = {1, 2, 3, 4, 5}; // Just used for numbering the producer and consumer

    for (int i = 0; i < 5; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }
    for (int i = 0; i < 5; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(pro[i], NULL);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(con[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define MaxItems 5 // Maximum items a producer can produce or a consumer can consume
#define BufferSize 5 // Size of the buffer

int buffer[BufferSize];
int in = 0;
int out = 0;
pthread_mutex_t mutex;

void *producer(void *pno)
{
    int item;
    for (int i = 0; i < MaxItems; i++) {
        item = rand(); // Produce a random item

        // Acquire the mutex lock
        pthread_mutex_lock(&mutex);

        // If the buffer is full, wait for the consumer to consume
        while (((in + 1) % BufferSize) == out) {
            printf("Producer %d: Buffer is full. Waiting...\n", *((int *)pno));
            pthread_mutex_unlock(&mutex);
            usleep(100); // Sleep for a short time before checking again
            pthread_mutex_lock(&mutex);
        }

        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pno), buffer[in], in);
        in = (in + 1) % BufferSize;

        // Release the mutex lock
        pthread_mutex_unlock(&mutex);
    }
}

void *consumer(void *cno)
{
    int item;
    for (int i = 0; i < MaxItems; i++) {

        // Acquire the mutex lock
        pthread_mutex_lock(&mutex);

        // If the buffer is empty, wait for the producer to produce
        while (in == out) {
            printf("Consumer %d: Buffer is empty. Waiting...\n", *((int *)cno));
            pthread_mutex_unlock(&mutex);
            usleep(100); // Sleep for a short time before checking again
            pthread_mutex_lock(&mutex);
        }

        item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n", *((int *)cno), item, out);
        out = (out + 1) % BufferSize;

        // Release the mutex lock
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t pro[5], con[5];
    pthread_mutex_init(&mutex, NULL);

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

    pthread_mutex_destroy(&mutex);

    return 0;
}

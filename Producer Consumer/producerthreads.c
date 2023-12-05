#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MaxItems 5
#define BufferSize 5

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

int in = 0;
int out = 0;
int buffer[BufferSize];
int bufferCount = 0;
int capacity = BufferSize;

void *producer(void *pno)
{
    int item;
    for (int i = 0; i < MaxItems; i++)
    {
        item = rand();
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pno), buffer[in], in);
        in = (in + 1) % capacity;
        bufferCount++;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        usleep(100000); // Sleep for a short time to simulate variable production time
    }
}

void *consumer(void *cno)
{
    int item;
    for (int i = 0; i < MaxItems; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n", *((int *)cno), item, out);
        out = (out + 1) % capacity;
        bufferCount--;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        usleep(100000); // Sleep for a short time to simulate variable consumption time
    }
}

int main()
{
    pthread_t pro[5], con[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, capacity);
    sem_init(&full, 0, 0);

    int a[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&pro[i], NULL, producer, (void *)&a[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&con[i], NULL, consumer, (void *)&a[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(pro[i], NULL);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

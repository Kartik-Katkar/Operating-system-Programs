#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

sem_t x, y;
pthread_t readerthreads[100], writerthreads[100];
int readercount = 0;

void* reader(void* param)
{
    sem_wait(&x);
    readercount++;
    if (readercount == 1)
        sem_wait(&y);
    sem_post(&x);

    printf("%lu thread id Reader is inside\n", pthread_self());
    usleep(300000); // usleep is in microseconds

    sem_wait(&x);
    readercount--;
    if (readercount == 0)
    {
        sem_post(&y);
    }
    sem_post(&x);

    printf("%lu thread id Reader has left\n", pthread_self());
    return NULL;
}

void* writer(void* param)
{
    printf("Writer with thread id : %lu is checking to enter\n", pthread_self());
    sem_wait(&y);

    printf("Writer with thread id : %lu is writing\n", pthread_self());
    usleep(300000); // usleep is in microseconds

    sem_post(&y);

    printf("Writer with thread id : %lu has finished writing \n", pthread_self());
    return NULL;
}

int main()
{
    int num_readers, num_writers;
    printf("Enter the number of readers: ");
    scanf("%d", &num_readers);

    printf("Enter the number of writers: ");
    scanf("%d", &num_writers);

    sem_init(&x, 0, 1);
    sem_init(&y, 0, 1);

    for (int i = 0; i < num_readers; i++)
    {
        pthread_create(&readerthreads[i], NULL, reader, NULL);
    }

    for (int i = 0; i < num_writers; i++)
    {
        pthread_create(&writerthreads[i], NULL, writer, NULL);
    }

    for (int i = 0; i < num_readers; i++)
    {
        pthread_join(readerthreads[i], NULL);
    }

    for (int i = 0; i < num_writers; i++)
    {
        pthread_join(writerthreads[i], NULL);
    }

    sem_destroy(&x);
    sem_destroy(&y);

    return 0;
}
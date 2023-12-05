#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define BUFFER_SIZE 10
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

sem_t sema;
int buffer[BUFFER_SIZE];
int count = 0;

void *producer(void *arg) {
    int item;
    while (1) {
        item = rand() % 5 + 1; 

        sem_wait(&sema);
        if(count<10)
        {
            buffer[count++] = item;
        printf("Producer %d produced: %d\n", *((int *)arg), item);
        }
        
        sem_post(&sema);

        sleep(1); 
    }
}

void *consumer(void *arg) {
    int item;
    while (1) {
        sem_wait(&sema);

        if(count>0)
        {
            item = buffer[--count];
        printf("Consumer %d consumed: %d\n", *((int *)arg), item);
       }
       sem_post(&sema);

        sleep(1);
    }
}

int main() {
    pthread_t producer_threads[NUM_PRODUCERS];
    pthread_t consumer_threads[NUM_CONSUMERS];
    int i;

    int producer_ids[NUM_PRODUCERS];
    int consumer_ids[NUM_CONSUMERS];

    sem_init(&sema,0,1);

    for (i = 0; i < NUM_PRODUCERS; i++) {
        producer_ids[i] = i + 1;
        pthread_create(&producer_threads[i], NULL, producer, &producer_ids[i]);

    }

    for (i = 0; i < NUM_CONSUMERS; i++) {
        consumer_ids[i] = i + 1;
        pthread_create(&consumer_threads[i], NULL, consumer, &consumer_ids[i]);
    }

    for (i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producer_threads[i], NULL);
    }

    for (i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumer_threads[i], NULL);
    }

    sem_destroy(&sema);

    return 0;
}

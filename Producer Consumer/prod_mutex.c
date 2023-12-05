#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

pthread_mutex_t mutex;
int buffer[BUFFER_SIZE];
int count = 0;

void *producer(void *arg) {
    int item;
    while (1) {
        // item = rand() % 10; // Generate a random item to produce

        pthread_mutex_lock(&mutex);
        if(count<5)
        {item = rand() % 10; 
            buffer[count++] = item;
        printf("Producer %d produced: %d\n", *((int *)arg), item);
        }
        
        pthread_mutex_unlock(&mutex);

        sleep(1); 
    }
}

void *consumer(void *arg) {
    int item;
    while (1) {
        pthread_mutex_lock(&mutex);

        if(count>0)
        {
        item = buffer[--count];
        printf("Consumer %d consumed: %d\n", *((int *)arg), item);
       }
        pthread_mutex_unlock(&mutex);

        sleep(1); 
    }
}

int main() {
    pthread_t producer_threads[NUM_PRODUCERS];
    pthread_t consumer_threads[NUM_CONSUMERS];
    int i;

    int producer_ids[NUM_PRODUCERS];
    int consumer_ids[NUM_CONSUMERS];

    pthread_mutex_init(&mutex, NULL);

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

    pthread_mutex_destroy(&mutex);

    return 0;
}

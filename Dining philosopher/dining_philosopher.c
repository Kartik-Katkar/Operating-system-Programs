#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define MAX_EAT 5

int *state;
int *philosophers;
sem_t mutex;
sem_t waiter;
sem_t *semaphores;
int num_philosophers;

void test(int i) {
    if (state[i] == HUNGRY && state[(i + num_philosophers - 1) % num_philosophers] != EATING && state[(i + 1) % num_philosophers] != EATING) {
        state[i] = EATING;
        sem_post(&semaphores[i]);
    }
}

void pickup_forks(int i) {
    sem_wait(&waiter);
    sem_wait(&mutex);
    state[i] = HUNGRY;
    test(i);
    sem_post(&mutex);
    sem_wait(&semaphores[i]);
    sem_post(&waiter);
}

void return_forks(int i) {
    sem_wait(&mutex);
    state[i] = THINKING;
    test((i + num_philosophers - 1) % num_philosophers);
    test((i + 1) % num_philosophers);
    sem_post(&mutex);
}

void* philosopher(void* arg) {
    int i = *(int*)arg;
    int eat_count = 0;
    while (eat_count < MAX_EAT) {
        printf("Philosopher %d (Thread %lu) is thinking\n", i, pthread_self());
        if (i % 2 == 0) {
            printf("Philosopher %d (Thread %lu) is hungry\n", i, pthread_self());
            pickup_forks(i);
            printf("Philosopher %d (Thread %lu) is eating\n", i, pthread_self());
            return_forks(i);
        } else {
            printf("Philosopher %d (Thread %lu) is hungry\n", i, pthread_self());
            pickup_forks((i + 1) % num_philosophers);
            printf("Philosopher %d (Thread %lu) is eating\n", i, pthread_self());
            return_forks((i + 1) % num_philosophers);
        }
        eat_count++;
    }
    printf("Philosopher %d (Thread %lu) has finished eating and is leaving the table\n", i, pthread_self()); // Indicate that philosopher has finished eating and is leaving
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number of philosophers>\n", argv[0]);
        return EXIT_FAILURE;
    }

    num_philosophers = atoi(argv[1]);
    pthread_t* threads = malloc(num_philosophers * sizeof(pthread_t));
    state = malloc(num_philosophers * sizeof(int));
    philosophers = malloc(num_philosophers * sizeof(int));
    semaphores = malloc(num_philosophers * sizeof(sem_t));

    sem_init(&mutex, 0, 1);
    sem_init(&waiter, 0, num_philosophers - 1);

    for (int i = 0; i < num_philosophers; ++i) {
        philosophers[i] = i;
        state[i] = THINKING;
        sem_init(&semaphores[i], 0, 0);
        pthread_create(&threads[i], NULL, philosopher, &philosophers[i]);
    }

    for (int i = 0; i < num_philosophers; ++i)
        pthread_join(threads[i], NULL);

    free(threads);
    free(state);
    free(philosophers);
    free(semaphores);

    return EXIT_SUCCESS;
}

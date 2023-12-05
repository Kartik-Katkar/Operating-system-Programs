#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 1

pthread_mutex_t reader_sem;
pthread_mutex_t writer_sem;
int shared_resource = 0;
int reader_count = 0;

void *reader(void *arg) {
    int reader_id = (int)arg;
    while (1) {
        pthread_mutex_lock(&reader_sem);

        // Lock for writers
        if (reader_count == 0) {
            pthread_mutex_lock(&writer_sem);
        }

        reader_count++;

        pthread_mutex_unlock(&reader_sem);

        // Read the shared resource
        printf("Reader %d entered the critical section\n", reader_id);
        printf("Reader %d read: %d\n", reader_id, shared_resource);
        printf("Reader %d exited the critical section\n", reader_id);

        pthread_mutex_lock(&reader_sem);

        reader_count--;

        if (reader_count == 0) {
            // Unlock for writers
            pthread_mutex_unlock(&writer_sem);
        }

        pthread_mutex_unlock(&reader_sem);

        // Simulate reading time
        sleep(5);
    }
}

void *writer(void *arg) {
    int writer_id =(int)arg;
    while (1) {
        pthread_mutex_lock(&writer_sem);

        // Write to the shared resource
        shared_resource++;
        printf("Writer %d entered the critical section\n", writer_id);
        printf("Writer %d wrote: %d\n", writer_id, shared_resource);

        pthread_mutex_unlock(&writer_sem);

        printf("Writer %d exited the critical section\n", writer_id);

        // Simulate writing time
        sleep(2);
    }
}

int main() {
    pthread_t reader_threads[NUM_READERS];
    pthread_t writer_threads[NUM_WRITERS];
    int i;

    pthread_mutex_init(&reader_sem, NULL);
    pthread_mutex_init(&writer_sem, NULL);

    for (i = 0; i <= NUM_READERS; i++) {
        pthread_create(&reader_threads[i], NULL, reader,i+1);
    }

    for (i = 0; i <= NUM_WRITERS; i++) {
        pthread_create(&writer_threads[i], NULL, writer,i+1);
    }

    for (i = 0; i < NUM_READERS; i++) {
        pthread_join(reader_threads[i], NULL);
    }

    for (i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writer_threads[i], NULL);
    }

    return 0;
}

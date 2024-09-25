
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define NUM_PRODUCERS 5
#define NUM_CONSUMERS 5

// Shared buffer
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

// Semaphores
sem_t empty;
sem_t full;
sem_t mutex;

// Producer function
void* producer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        // Produce item
        item = rand() % 100;
        printf("Produced: %d\n", item);

        // Wait for empty slot
        sem_wait(&empty);
        sem_wait(&mutex);

        // Add item to buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        printf("Buffer: ");
        for (int j = 0; j < BUFFER_SIZE; j++) {
            printf("%d ", buffer[j]);
        }
        printf("\n");

        // Signal that buffer is not empty
        sem_post(&mutex);
        sem_post(&full);

        // Sleep for 1 second
        sleep(1);
    }
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        // Wait for full slot
        sem_wait(&full);
        sem_wait(&mutex);

        // Remove item from buffer
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumed: %d\n", item);
        printf("Buffer: ");
        for (int j = 0; j < BUFFER_SIZE; j++) {
            printf("%d ", buffer[j]);
        }
        printf("\n");

        // Signal that buffer is not full
        sem_post(&mutex);
        sem_post(&empty);

        // Sleep for 1 second
        sleep(1);
    }
    return NULL;
}

int main() {
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // Create producer threads
    pthread_t producer_threads[NUM_PRODUCERS];
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&producer_threads[i], NULL, producer, NULL);
    }

    // Create consumer threads
    pthread_t consumer_threads[NUM_CONSUMERS];
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumer_threads[i], NULL, consumer, NULL);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producer_threads[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumer_threads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}


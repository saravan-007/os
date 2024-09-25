
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 5

// Semaphores
sem_t mutex, writeblock;

// Shared resource
int data = 0;
int readerCount = 0;

// Writer function
void* writer(void* arg) {
    int writerID = *(int*) arg;

    while (1) {
        // Wait for writeblock semaphore
        sem_wait(&writeblock);

        // Write to shared resource
        data++;
        printf("Writer %d: Wrote data = %d\n", writerID, data);

        // Signal writeblock semaphore
        sem_post(&writeblock);

        sleep(1);
    }
    return NULL;
}

// Reader function
void* reader(void* arg) {
    int readerID = *(int*) arg;

    while (1) {
        // Wait for mutex semaphore
        sem_wait(&mutex);

        // Increment reader count
        readerCount++;

        // If first reader, wait for writeblock semaphore
        if (readerCount == 1) {
            sem_wait(&writeblock);
        }

        // Read from shared resource
        printf("Reader %d: Read data = %d\n", readerID, data);

        // Signal mutex semaphore
        sem_post(&mutex);

        // Decrement reader count
        sem_wait(&mutex);
        readerCount--;

        // If last reader, signal writeblock semaphore
        if (readerCount == 0) {
            sem_post(&writeblock);
        }
        sem_post(&mutex);

        sleep(1);
    }
    return NULL;
}

int main() {
    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&writeblock, 0, 1);

    // Create writer threads
    int writerIDs[NUM_WRITERS];
    pthread_t writerThreads[NUM_WRITERS];
    for (int i = 0; i < NUM_WRITERS; i++) {
        writerIDs[i] = i;
        pthread_create(&writerThreads[i], NULL, writer, &writerIDs[i]);
    }

    // Create reader threads
    int readerIDs[NUM_READERS];
    pthread_t readerThreads[NUM_READERS];
    for (int i = 0; i < NUM_READERS; i++) {
        readerIDs[i] = i;
        pthread_create(&readerThreads[i], NULL, reader, &readerIDs[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writerThreads[i], NULL);
    }
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readerThreads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&writeblock);

    return 0;
}


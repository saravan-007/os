
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

// Shared resource
int sharedVariable = 0;

// Mutex lock
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Thread function
void* threadFunction(void* arg) {
    int threadID = *(int*) arg;

    // Lock mutex
    pthread_mutex_lock(&mutex);

    printf("Thread %d: Lock acquired\n", threadID);

    // Critical section
    for (int i = 0; i < 5; i++) {
        sharedVariable++;
        printf("Thread %d: Shared variable = %d\n", threadID, sharedVariable);
        sleep(1);
    }

    // Unlock mutex
    pthread_mutex_unlock(&mutex);

    printf("Thread %d: Lock released\n", threadID);

    return NULL;
}

int main() {
    int threadIDs[NUM_THREADS];
    pthread_t threads[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        threadIDs[i] = i;
        pthread_create(&threads[i], NULL, threadFunction, &threadIDs[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}


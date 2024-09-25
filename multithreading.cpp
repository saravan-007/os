
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Function to be executed by thread 1
void* thread1_func(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Thread 1: %d\n", i);
        sleep(1); // Simulate work
    }
    return NULL;
}

// Function to be executed by thread 2
void* thread2_func(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Thread 2: %d\n", i);
        sleep(1); // Simulate work
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Create thread 1
    if (pthread_create(&thread1, NULL, thread1_func, NULL) != 0) {
        perror("pthread_create");
        exit(1);
    }

    // Create thread 2
    if (pthread_create(&thread2, NULL, thread2_func, NULL) != 0) {
        perror("pthread_create");
        exit(1);
    }

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Main thread: Threads finished\n");

    return 0;
}


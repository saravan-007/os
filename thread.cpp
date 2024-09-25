
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* threadFunction1(void* arg) {
    printf("Thread 1 started\n");
    sleep(2);
    printf("Thread 1 finished\n");
    pthread_exit(NULL);
}

void* threadFunction2(void* arg) {
    printf("Thread 2 started\n");
    sleep(2);
    printf("Thread 2 finished\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    int ret1, ret2;

    // Create threads
    ret1 = pthread_create(&thread1, NULL, threadFunction1, NULL);
    ret2 = pthread_create(&thread2, NULL, threadFunction2, NULL);
    if (ret1 != 0 || ret2 != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    printf("Thread 1 ID: %lu\n", thread1);
    printf("Thread 2 ID: %lu\n", thread2);

    // Check if threads are equal
    if (thread1 == thread2) {
        printf("Threads are equal\n");
    } else {
        printf("Threads are not equal\n");
    }

    // Join threads
    printf("Main thread waiting for Thread 1 to join\n");
    pthread_join(thread1, NULL);
    printf("Thread 1 joined\n");

    printf("Main thread waiting for Thread 2 to join\n");
    pthread_join(thread2, NULL);
    printf("Thread 2 joined\n");

    // Cancel Thread 2 (already joined, so no effect)
    pthread_cancel(thread2);

    printf("Main thread exiting\n");
    return 0;
}


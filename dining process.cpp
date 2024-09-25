#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define EATING_TIME 2
#define THINKING_TIME 2

sem_t fork_sem[NUM_PHILOSOPHERS];
pthread_t philosopher_threads[NUM_PHILOSOPHERS];

void* philosopher(void* arg) {
    int id = *(int*)arg;
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking\n", id);
        sleep(THINKING_TIME);

        // Pick up left fork
        sem_wait(&fork_sem[left_fork]);
        printf("Philosopher %d picked up left fork %d\n", id, left_fork);

        // Pick up right fork
        sem_wait(&fork_sem[right_fork]);
        printf("Philosopher %d picked up right fork %d\n", id, right_fork);

        // Eating
        printf("Philosopher %d is eating\n", id);
        sleep(EATING_TIME);

        // Put down right fork
        sem_post(&fork_sem[right_fork]);
        printf("Philosopher %d put down right fork %d\n", id, right_fork);

        // Put down left fork
        sem_post(&fork_sem[left_fork]);
        printf("Philosopher %d put down left fork %d\n", id, left_fork);
    }
}

int main() {
    int ids[NUM_PHILOSOPHERS];

    // Initialize semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&fork_sem[i], 0, 1);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosopher_threads[i], NULL, philosopher, &ids[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosopher_threads[i], NULL);
    }

    return 0;
}


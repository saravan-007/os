
#include <stdio.h>

#define NUM_PROCESSES 5
#define NUM_RESOURCES 3

// Available resources
int available[NUM_RESOURCES] = {3, 3, 2};

// Maximum resources required by each process
int max[NUM_PROCESSES][NUM_RESOURCES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

// Currently allocated resources to each process
int allocation[NUM_PROCESSES][NUM_RESOURCES] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

// Need matrix
int need[NUM_PROCESSES][NUM_RESOURCES];

// Function to check if a process can be allocated resources
int canAllocate(int process) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (need[process][i] > available[i]) {
            return 0;
        }
    }
    return 1;
}

// Function to allocate resources to a process
void allocateResources(int process) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        available[i] -= need[process][i];
        allocation[process][i] += need[process][i];
        need[process][i] = 0;
    }
}

// Function to deallocate resources from a process
void deallocateResources(int process) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        available[i] += allocation[process][i];
        allocation[process][i] = 0;
    }
}

// Function to display the system state
void displayState() {
    printf("Available Resources: ");
    for (int i = 0; i < NUM_RESOURCES; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");

    printf("Allocation Matrix:\n");
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    printf("Need Matrix:\n");
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Initialize need matrix
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    displayState();

    // Request resources for process 2
    int request[] = {1, 0, 0};
    int process = 2;

    // Check if request can be allocated
    for (int i = 0; i < NUM_RESOURCES; i++) {
        need[process][i] += request[i];
    }

    if (canAllocate(process)) {
        allocateResources(process);
        printf("Request allocated successfully\n");
    } else {
        printf("Request cannot be allocated\n");
    }

    displayState();

    return 0;
}


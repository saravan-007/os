#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

// Structure to represent a disk request
typedef struct Request {
    int cylinderNumber;
    int arrivalTime;
} Request;

// Function to calculate the total seek time using FCFS
int fcfsDiskScheduling(Request requests[], int numRequests, int initialHeadPosition) {
    int totalSeekTime = 0;
    int currentHeadPosition = initialHeadPosition;

    printf("Request Order:\n");
    for (int i = 0; i < numRequests; i++) {
        printf("Cylinder %d (Arrival Time: %d)\n", requests[i].cylinderNumber, requests[i].arrivalTime);

        // Calculate seek time
        int seekTime = abs(currentHeadPosition - requests[i].cylinderNumber);
        totalSeekTime += seekTime;
        printf("Seek Time: %d\n", seekTime);

        // Update current head position
        currentHeadPosition = requests[i].cylinderNumber;
    }

    printf("Total Seek Time: %d\n", totalSeekTime);
    return totalSeekTime;
}

int main() {
    int numRequests;
    printf("Enter number of disk requests: ");
    scanf("%d", &numRequests);

    Request requests[MAX_REQUESTS];
    printf("Enter cylinder numbers and arrival times:\n");
    for (int i = 0; i < numRequests; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d %d", &requests[i].cylinderNumber, &requests[i].arrivalTime);
    }

    int initialHeadPosition;
    printf("Enter initial head position: ");
    scanf("%d", &initialHeadPosition);

    fcfsDiskScheduling(requests, numRequests, initialHeadPosition);

    return 0;
}



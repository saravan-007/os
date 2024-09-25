
#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

// Structure to represent a disk request
typedef struct Request {
    int cylinderNumber;
    int arrivalTime;
} Request;

// Function to sort requests based on arrival time
void sortRequests(Request requests[], int numRequests) {
    for (int i = 0; i < numRequests - 1; i++) {
        for (int j = i + 1; j < numRequests; j++) {
            if (requests[i].arrivalTime > requests[j].arrivalTime) {
                Request temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }
}

// Function to calculate the total seek time using SCAN
int scanDiskScheduling(Request requests[], int numRequests, int initialHeadPosition) {
    int totalSeekTime = 0;
    int currentHeadPosition = initialHeadPosition;
    int left = 0, right = numRequests - 1;

    // Sort requests based on arrival time
    sortRequests(requests, numRequests);

    printf("Request Order:\n");
    while (left <= right) {
        // Find the closest request to the left
        int closestLeft = -1;
        for (int i = left; i <= right; i++) {
            if (requests[i].cylinderNumber <= currentHeadPosition && requests[i].arrivalTime <= totalSeekTime) {
                if (closestLeft == -1 || abs(currentHeadPosition - requests[i].cylinderNumber) < abs(currentHeadPosition - requests[closestLeft].cylinderNumber)) {
                    closestLeft = i;
                }
            }
        }

        // If no request to the left, move to the right
        if (closestLeft == -1) {
            // Find the closest request to the right
            int closestRight = -1;
            for (int i = left; i <= right; i++) {
                if (requests[i].cylinderNumber > currentHeadPosition && requests[i].arrivalTime <= totalSeekTime) {
                    if (closestRight == -1 || abs(currentHeadPosition - requests[i].cylinderNumber) < abs(currentHeadPosition - requests[closestRight].cylinderNumber)) {
                        closestRight = i;
                    }
                }
            }

            // Move to the right
            if (closestRight != -1) {
                int seekTime = abs(currentHeadPosition - requests[closestRight].cylinderNumber);
                totalSeekTime += seekTime;
                printf("Seek Time: %d (Cylinder %d)\n", seekTime, requests[closestRight].cylinderNumber);
                currentHeadPosition = requests[closestRight].cylinderNumber;
                for (int i = closestRight; i < right; i++) {
                    requests[i] = requests[i + 1];
                }
                right--;
            } else {
                break;
            }
        } else {
            // Move to the left
            int seekTime = abs(currentHeadPosition - requests[closestLeft].cylinderNumber);
            totalSeekTime += seekTime;
            printf("Seek Time: %d (Cylinder %d)\n", seekTime, requests[closestLeft].cylinderNumber);
            currentHeadPosition = requests[closestLeft].cylinderNumber;
            for (int i = closestLeft; i < right; i++) {
                requests[i] = requests[i + 1];
            }
            right--;
        }
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

    scanDiskScheduling(requests, numRequests, initialHeadPosition);

    return 0;
}


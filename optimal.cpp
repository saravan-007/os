
#include <stdio.h>
#include <stdlib.h>

#define PAGE_TABLE_SIZE 5
#define REFERENCE_STRING_SIZE 20

// Function to find the optimal page replacement
int findOptimalPage(int pageTable[], int referenceString[], int currentIndex) {
    int optimalIndex = 0;
    int maxDistance = 0;

    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        int distance = 0;
        for (int j = currentIndex; j < REFERENCE_STRING_SIZE; j++) {
            if (pageTable[i] == referenceString[j]) {
                distance = j - currentIndex;
                break;
            } else if (j == REFERENCE_STRING_SIZE - 1) {
                distance = REFERENCE_STRING_SIZE - currentIndex;
            }
        }

        if (distance > maxDistance) {
            maxDistance = distance;
            optimalIndex = i;
        }
    }

    return optimalIndex;
}

// Function to handle page faults using Optimal
void optimalPageReplacement(int referenceString[], int pageSize) {
    int pageFaults = 0;
    int pageTable[PAGE_TABLE_SIZE];

    // Initialize page table with empty pages
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        pageTable[i] = -1;
    }

    printf("Reference String: ");
    for (int i = 0; i < REFERENCE_STRING_SIZE; i++) {
        printf("%d ", referenceString[i]);
    }
    printf("\n");

    for (int i = 0; i < REFERENCE_STRING_SIZE; i++) {
        int currentPage = referenceString[i];
        int pageFound = 0;

        // Check if page is already in page table
        for (int j = 0; j < PAGE_TABLE_SIZE; j++) {
            if (pageTable[j] == currentPage) {
                pageFound = 1;
                break;
            }
        }

        // If page not found, handle page fault
        if (!pageFound) {
            pageFaults++;

            // If page table is empty, add page
            if (i < PAGE_TABLE_SIZE) {
                pageTable[i] = currentPage;
            } else {
                // Find optimal page to replace
                int optimalIndex = findOptimalPage(pageTable, referenceString, i);
                pageTable[optimalIndex] = currentPage;
            }

            printf("Page Fault: Replace Page %d with Page %d\n", pageTable[i % PAGE_TABLE_SIZE], currentPage);
        } else {
            printf("Page Hit: Page %d already in memory\n", currentPage);
        }

        // Display current page table
        printf("Page Table: ");
        for (int j = 0; j < PAGE_TABLE_SIZE; j++) {
            printf("%d ", pageTable[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int referenceString[REFERENCE_STRING_SIZE] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int pageSize = PAGE_TABLE_SIZE;

    optimalPageReplacement(referenceString, pageSize);

    return 0;
}



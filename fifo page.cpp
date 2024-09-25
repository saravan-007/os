
#include <stdio.h>
#include <stdlib.h>

#define PAGE_TABLE_SIZE 5
#define REFERENCE_STRING_SIZE 20

// Function to handle page faults using FIFO
void fifoPageReplacement(int referenceString[], int pageSize) {
    int pageFaults = 0;
    int pageTable[PAGE_TABLE_SIZE];
    int indexOfOldestPage = 0;

    // Initialize page table with -1 (empty pages)
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

            // Replace oldest page with new page
            pageTable[indexOfOldestPage] = currentPage;
            indexOfOldestPage = (indexOfOldestPage + 1) % PAGE_TABLE_SIZE;

            printf("Page Fault: Replace Page %d with Page %d\n", pageTable[indexOfOldestPage - 1], currentPage);
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

    fifoPageReplacement(referenceString, pageSize);

    return 0;
}



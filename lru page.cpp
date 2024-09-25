
#include <stdio.h>
#include <stdlib.h>

#define PAGE_TABLE_SIZE 5
#define REFERENCE_STRING_SIZE 20

// Structure to represent a page in the page table
typedef struct Page {
    int pageNumber;
    int lastIndex; // Index of last access
} Page;

// Function to find the LRU page (least recently used)
int findLRUPage(Page pageTable[], int currentTime) {
    int lruIndex = 0;
    int minLastIndex = pageTable[0].lastIndex;

    for (int i = 1; i < PAGE_TABLE_SIZE; i++) {
        if (pageTable[i].lastIndex < minLastIndex) {
            minLastIndex = pageTable[i].lastIndex;
            lruIndex = i;
        }
    }

    return lruIndex;
}

// Function to handle page faults using LRU
void lruPageReplacement(int referenceString[], int pageSize) {
    int pageFaults = 0;
    Page pageTable[PAGE_TABLE_SIZE];

    // Initialize page table with empty pages
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        pageTable[i].pageNumber = -1;
        pageTable[i].lastIndex = -1;
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
            if (pageTable[j].pageNumber == currentPage) {
                pageFound = 1;
                pageTable[j].lastIndex = i; // Update last access index
                break;
            }
        }

        // If page not found, handle page fault
        if (!pageFound) {
            pageFaults++;

            // Find LRU page and replace it
            int lruIndex = findLRUPage(pageTable, i);
            pageTable[lruIndex].pageNumber = currentPage;
            pageTable[lruIndex].lastIndex = i;

            printf("Page Fault: Replace Page %d with Page %d\n", pageTable[lruIndex].pageNumber, currentPage);
        } else {
            printf("Page Hit: Page %d already in memory\n", currentPage);
        }

        // Display current page table
        printf("Page Table: ");
        for (int j = 0; j < PAGE_TABLE_SIZE; j++) {
            printf("%d ", pageTable[j].pageNumber);
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int referenceString[REFERENCE_STRING_SIZE] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int pageSize = PAGE_TABLE_SIZE;

    lruPageReplacement(referenceString, pageSize);

    return 0;
}


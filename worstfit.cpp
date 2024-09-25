
#include <stdio.h>
#include <stdlib.h>

// Structure to represent a block of memory
typedef struct Block {
    int size;
    int allocated;
} Block;

// Function to find the worst fit block
int worstFit(Block* memoryBlocks, int numBlocks, int blockSize) {
    int worstIndex = -1;
    int maxWaste = 0;

    for (int i = 0; i < numBlocks; i++) {
        if (!memoryBlocks[i].allocated && memoryBlocks[i].size >= blockSize) {
            int waste = memoryBlocks[i].size - blockSize;
            if (waste > maxWaste) {
                maxWaste = waste;
                worstIndex = i;
            }
        }
    }

    return worstIndex;
}

// Function to allocate memory using worst fit algorithm
void allocateMemory(Block* memoryBlocks, int numBlocks, int blockSize) {
    int index = worstFit(memoryBlocks, numBlocks, blockSize);

    if (index != -1) {
        memoryBlocks[index].allocated = 1;
        printf("Memory allocated: Block %d, Size %d\n", index, blockSize);
    } else {
        printf("Memory allocation failed: Insufficient memory\n");
    }
}

// Function to deallocate memory
void deallocateMemory(Block* memoryBlocks, int numBlocks, int blockIndex) {
    if (blockIndex >= 0 && blockIndex < numBlocks && memoryBlocks[blockIndex].allocated) {
        memoryBlocks[blockIndex].allocated = 0;
        printf("Memory deallocated: Block %d\n", blockIndex);
    } else {
        printf("Memory deallocation failed: Invalid block index\n");
    }
}

// Function to display memory blocks
void displayMemory(Block* memoryBlocks, int numBlocks) {
    printf("Memory Blocks:\n");
    for (int i = 0; i < numBlocks; i++) {
        printf("Block %d: Size %d, Allocated %s\n", i, memoryBlocks[i].size, memoryBlocks[i].allocated ? "Yes" : "No");
    }
}

int main() {
    int numBlocks;
    printf("Enter number of memory blocks: ");
    scanf("%d", &numBlocks);

    Block* memoryBlocks = (Block*) malloc(numBlocks * sizeof(Block));

    printf("Enter size of each memory block:\n");
    for (int i = 0; i < numBlocks; i++) {
        printf("Block %d: ", i);
        scanf("%d", &memoryBlocks[i].size);
        memoryBlocks[i].allocated = 0;
    }

    while (1) {
        printf("\nMemory Management Menu:\n");
        printf("1. Allocate Memory\n");
        printf("2. Deallocate Memory\n");
        printf("3. Display Memory Blocks\n");
        printf("4. Exit\n");
        printf("Enter choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int blockSize;
                printf("Enter block size to allocate: ");
                scanf("%d", &blockSize);
                allocateMemory(memoryBlocks, numBlocks, blockSize);
                break;
            }
            case 2: {
                int blockIndex;
                printf("Enter block index to deallocate: ");
                scanf("%d", &blockIndex);
                deallocateMemory(memoryBlocks, numBlocks, blockIndex);
                break;
            }
            case 3:
                displayMemory(memoryBlocks, numBlocks);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }

    free(memoryBlocks);
    return 0;
}


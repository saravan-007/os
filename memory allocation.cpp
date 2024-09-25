#include <stdio.h>
#include <stdlib.h>

typedef struct MemoryBlock {
    int size;
    int isFree;
    struct MemoryBlock* next;
} MemoryBlock;

MemoryBlock* memoryStart;

void initMemory(int size) {
    memoryStart = (MemoryBlock*) malloc(sizeof(MemoryBlock));
    memoryStart->size = size;
    memoryStart->isFree = 1;
    memoryStart->next = NULL;
}

void* firstFitAlloc(int size) {
    MemoryBlock* current = memoryStart;
    while (current != NULL) {
        if (current->isFree && current->size >= size) {
            current->isFree = 0;
            return (void*) ((char*) current + sizeof(MemoryBlock));
        }
        current = current->next;
    }
    return NULL;
}

void* bestFitAlloc(int size) {
    MemoryBlock* best = NULL;
    MemoryBlock* current = memoryStart;
    while (current != NULL) {
        if (current->isFree && current->size >= size && (best == NULL || current->size < best->size)) {
            best = current;
        }
        current = current->next;
    }
    if (best != NULL) {
        best->isFree = 0;
        return (void*) ((char*) best + sizeof(MemoryBlock));
    }
    return NULL;
}

void* worstFitAlloc(int size) {
    MemoryBlock* worst = NULL;
    MemoryBlock* current = memoryStart;
    while (current != NULL) {
        if (current->isFree && current->size >= size && (worst == NULL || current->size > worst->size)) {
            worst = current;
        }
        current = current->next;
    }
    if (worst != NULL) {
        worst->isFree = 0;
        return (void*) ((char*) worst + sizeof(MemoryBlock));
    }
    return NULL;
}

void freeMemory(void* ptr) {
    MemoryBlock* block = (MemoryBlock*) ((char*) ptr - sizeof(MemoryBlock));
    block->isFree = 1;
}

void addMemoryBlock(int size) {
    MemoryBlock* newBlock = (MemoryBlock*) malloc(sizeof(MemoryBlock));
    newBlock->size = size;
    newBlock->isFree = 1;
    newBlock->next = NULL;

    MemoryBlock* current = memoryStart;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newBlock;
}

int main() {
    int memorySize = 1024;
    initMemory(memorySize);

    // Add more memory blocks
    addMemoryBlock(512);
    addMemoryBlock(256);

    // Test memory allocation strategies
    void* ptr1 = firstFitAlloc(100);
    void* ptr2 = bestFitAlloc(200);
    void* ptr3 = worstFitAlloc(50);

    printf("Allocated addresses: %p, %p, %p\n", ptr1, ptr2, ptr3);

    // Free memory
    freeMemory(ptr1);
    freeMemory(ptr2);
    freeMemory(ptr3);

    return 0;
}



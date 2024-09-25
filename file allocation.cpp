
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FILES 10
#define MAX_BLOCKS 100
#define BLOCK_SIZE 1024

// Structure to represent a file
typedef struct File {
    char fileName[50];
    int fileSize;
    int* blocks; // Array of block indices
} File;

// Structure to represent the file system
typedef struct FileSystem {
    File files[MAX_FILES];
    int fileCount;
    int blockCount;
    int freeBlocks[MAX_BLOCKS];
} FileSystem;

// Function to initialize the file system
void initFileSystem(FileSystem* fs) {
    fs->fileCount = 0;
    fs->blockCount = MAX_BLOCKS;
    for (int i = 0; i < MAX_BLOCKS; i++) {
        fs->freeBlocks[i] = i;
    }
}

// Function to create a new file
void createFile(FileSystem* fs, char* fileName, int fileSize) {
    if (fs->fileCount < MAX_FILES) {
        File newFile;
        strcpy(newFile.fileName, fileName);
        newFile.fileSize = fileSize;
        newFile.blocks = (int*)malloc(fileSize * sizeof(int));

        // Allocate blocks for the file
        for (int i = 0; i < fileSize; i++) {
            if (fs->blockCount > 0) {
                newFile.blocks[i] = fs->freeBlocks[0];
                fs->freeBlocks[0] = fs->freeBlocks[fs->blockCount - 1];
                fs->blockCount--;
            } else {
                printf("Not enough free blocks\n");
                return;
            }
        }

        fs->files[fs->fileCount] = newFile;
        fs->fileCount++;
        printf("File created: %s\n", fileName);
    } else {
        printf("Maximum file limit reached\n");
    }
}

// Function to delete a file
void deleteFile(FileSystem* fs, char* fileName) {
    for (int i = 0; i < fs->fileCount; i++) {
        if (strcmp(fs->files[i].fileName, fileName) == 0) {
            // Free allocated blocks
            for (int j = 0; j < fs->files[i].fileSize; j++) {
                fs->freeBlocks[fs->blockCount] = fs->files[i].blocks[j];
                fs->blockCount++;
            }

            // Shift files to fill the gap
            for (int j = i; j < fs->fileCount - 1; j++) {
                fs->files[j] = fs->files[j + 1];
            }

            fs->fileCount--;
            printf("File deleted: %s\n", fileName);
            return;
        }
    }

    printf("File not found\n");
}

// Function to display file information
void displayFileInfo(FileSystem* fs, char* fileName) {
    for (int i = 0; i < fs->fileCount; i++) {
        if (strcmp(fs->files[i].fileName, fileName) == 0) {
            printf("File Name: %s\n", fs->files[i].fileName);
            printf("File Size: %d blocks\n", fs->files[i].fileSize);
            printf("Allocated Blocks: ");
            for (int j = 0; j < fs->files[i].fileSize; j++) {
                printf("%d ", fs->files[i].blocks[j]);
            }
            printf("\n");
            return;
        }
    }

    printf("File not found\n");
}

int main() {
    FileSystem fs;
    initFileSystem(&fs);

    createFile(&fs, "file1.txt", 5);
    createFile(&fs, "file2.txt", 3);
    displayFileInfo(&fs, "file1.txt");
    deleteFile(&fs, "file1.txt");
    displayFileInfo(&fs, "file2.txt");

    return 0;
}


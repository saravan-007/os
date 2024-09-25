
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_FILE_NAME 256
#define MAX_DIR_NAME 256

// Structure to represent a file
typedef struct File {
    char name[MAX_FILE_NAME];
    struct File* next;
} File;

// Structure to represent a directory
typedef struct Directory {
    char name[MAX_DIR_NAME];
    File* files;
} Directory;

// Function to create a new file
File* createFile(char* name) {
    File* newFile = (File*) malloc(sizeof(File));
    strcpy(newFile->name, name);
    newFile->next = NULL;
    return newFile;
}

// Function to add file to directory
void addFile(Directory* dir, File* file) {
    if (dir->files == NULL) {
        dir->files = file;
    } else {
        File* current = dir->files;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = file;
    }
}

// Function to display directory contents
void displayDirectory(Directory* dir) {
    printf("Directory: %s\n", dir->name);
    File* current = dir->files;
    while (current != NULL) {
        printf("File: %s\n", current->name);
        current = current->next;
    }
}

// Function to search for file in directory
File* searchFile(Directory* dir, char* name) {
    File* current = dir->files;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to delete file from directory
void deleteFile(Directory* dir, char* name) {
    if (dir->files == NULL) {
        printf("Directory is empty\n");
        return;
    }

    if (strcmp(dir->files->name, name) == 0) {
        File* temp = dir->files;
        dir->files = dir->files->next;
        free(temp);
        return;
    }

    File* current = dir->files;
    while (current->next != NULL) {
        if (strcmp(current->next->name, name) == 0) {
            File* temp = current->next;
            current->next = current->next->next;
            free(temp);
            return;
        }
        current = current->next;
    }
}

int main() {
    Directory dir;
    strcpy(dir.name, "MyDirectory");
    dir.files = NULL;

    // Create files and add to directory
    File* file1 = createFile("file1.txt");
    addFile(&dir, file1);

    File* file2 = createFile("file2.txt");
    addFile(&dir, file2);

    File* file3 = createFile("file3.txt");
    addFile(&dir, file3);

    // Display directory contents
    displayDirectory(&dir);

    // Search for file
    File* searchedFile = searchFile(&dir, "file2.txt");
    if (searchedFile != NULL) {
        printf("File found: %s\n", searchedFile->name);
    } else {
        printf("File not found\n");
    }

    // Delete file
    deleteFile(&dir, "file2.txt");

    // Display directory contents after deletion
    displayDirectory(&dir);

    return 0;
}


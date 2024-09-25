
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

// Function to create a file
void createFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
    } else {
        printf("File created: %s\n", filename);
        fclose(file);
    }
}

// Function to delete a file
void deleteFile(const char* filename) {
    if (remove(filename) == -1) {
        perror("Error deleting file");
    } else {
        printf("File deleted: %s\n", filename);
    }
}

// Function to copy a file
void copyFile(const char* srcFilename, const char* destFilename) {
    FILE* srcFile = fopen(srcFilename, "r");
    FILE* destFile = fopen(destFilename, "w");
    if (srcFile == NULL || destFile == NULL) {
        perror("Error copying file");
    } else {
        char buffer[1024];
        while (fread(buffer, 1, 1024, srcFile) == 1024) {
            fwrite(buffer, 1, 1024, destFile);
        }
        fclose(srcFile);
        fclose(destFile);
        printf("File copied: %s to %s\n", srcFilename, destFilename);
    }
}

// Function to rename a file
void renameFile(const char* oldFilename, const char* newFilename) {
    if (rename(oldFilename, newFilename) == -1) {
        perror("Error renaming file");
    } else {
        printf("File renamed: %s to %s\n", oldFilename, newFilename);
    }
}

// Function to display file contents
void displayFileContents(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
    } else {
        char buffer[1024];
        while (fread(buffer, 1, 1024, file) == 1024) {
            printf("%s", buffer);
        }
        fclose(file);
    }
}

// Function to list directory contents
void listDirectoryContents(const char* dirname) {
    DIR* dir = opendir(dirname);
    if (dir == NULL) {
        perror("Error opening directory");
    } else {
        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL) {
            printf("%s\n", entry->d_name);
        }
        closedir(dir);
    }
}

int main() {
    printf("File Management Operations:\n");

    char filename[] = "example.txt";
    createFile(filename);

    char srcFilename[] = "example.txt";
    char destFilename[] = "copy.txt";
    copyFile(srcFilename, destFilename);

    char oldFilename[] = "example.txt";
    char newFilename[] = "renamed.txt";
    renameFile(oldFilename, newFilename);

    displayFileContents(newFilename);

    char dirname[] = ".";
    listDirectoryContents(dirname);

    deleteFile(newFilename);
    deleteFile(destFilename);

    return 0;
}



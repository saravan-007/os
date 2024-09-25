
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

// Function to demonstrate fcntl system call
void demonstrateFcntl() {
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
    } else {
        printf("File descriptor: %d\n", fd);
        close(fd);
    }
}

// Function to demonstrate lseek system call
void demonstrateLseek() {
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
    } else {
        off_t offset = lseek(fd, 10, SEEK_SET);
        printf("New file offset: %lld\n", (long long) offset);
        close(fd);
    }
}

// Function to demonstrate stat system call
void demonstrateStat() {
    struct stat fileStat;
    if (stat("example.txt", &fileStat) == -1) {
        perror("Error retrieving file stats");
    } else {
        printf("File size: %lld bytes\n", (long long) fileStat.st_size);
        printf("File permissions: %o\n", fileStat.st_mode);
    }
}

// Function to demonstrate opendir and readdir system calls
void demonstrateOpendirReaddir() {
    DIR* dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
    } else {
        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL) {
            printf("File name: %s\n", entry->d_name);
        }
        closedir(dir);
    }
}

int main() {
    // Create a file for demonstration
    FILE* file = fopen("example.txt", "w");
    fprintf(file, "Hello, World!");
    fclose(file);

    // Demonstrate fcntl system call
    printf("Demonstrating fcntl:\n");
    demonstrateFcntl();

    // Demonstrate lseek system call
    printf("\nDemonstrating lseek:\n");
    demonstrateLseek();

    // Demonstrate stat system call
    printf("\nDemonstrating stat:\n");
    demonstrateStat();

    // Demonstrate opendir and readdir system calls
    printf("\nDemonstrating opendir and readdir:\n");
    demonstrateOpendirReaddir();

    // Remove the file
    remove("example.txt");

    return 0;
}



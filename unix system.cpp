
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

// Function to create a file
void createFile(const char* filename) {
    int fd = creat(filename, 0644);
    if (fd == -1) {
        perror("Error creating file");
    } else {
        printf("File created: %s\n", filename);
        close(fd);
    }
}

// Function to open an existing file
int openFile(const char* filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
    } else {
        printf("File opened: %s\n", filename);
    }
    return fd;
}

// Function to read from a file
void readFile(int fd) {
    char buffer[1024];
    ssize_t bytesRead = read(fd, buffer, 1024);
    if (bytesRead == -1) {
        perror("Error reading file");
    } else {
        printf("File contents: %s\n", buffer);
    }
}

// Function to write to a file
void writeFile(int fd, const char* data) {
    ssize_t bytesWritten = write(fd, data, strlen(data));
    if (bytesWritten == -1) {
        perror("Error writing to file");
    } else {
        printf("Data written to file\n");
    }
}

// Function to close a file
void closeFile(int fd) {
    if (close(fd) == -1) {
        perror("Error closing file");
    } else {
        printf("File closed\n");
    }
}

// Function to delete a file
void deleteFile(const char* filename) {
    if (unlink(filename) == -1) {
        perror("Error deleting file");
    } else {
        printf("File deleted: %s\n", filename);
    }
}

int main() {
    const char* filename = "example.txt";
    const char* data = "Hello, World!";

    // Create a file
    createFile(filename);

    // Open the file
    int fd = openFile(filename);

    // Write to the file
    writeFile(fd, data);

    // Close the file
    closeFile(fd);

    // Reopen the file
    fd = openFile(filename);

    // Read from the file
    readFile(fd);

    // Close the file
    closeFile(fd);

    // Delete the file
    deleteFile(filename);

    return 0;
}


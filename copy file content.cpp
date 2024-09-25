#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    int src_fd, dest_fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    char* src_file = "source.txt";
    char* dest_file = "destination.txt";
    src_fd = open(src_file, O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening source file");
        exit(1);
    }
    dest_fd = open(dest_file, O_WRONLY | O_CREAT, 0644);
    if (dest_fd == -1) {
        perror("Error opening destination file");
        close(src_fd);
        exit(1);
    }
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        write(dest_fd, buffer, bytes_read);
    }
    if (bytes_read == -1) {
        perror("Error reading source file");
    }
    close(src_fd);
    close(dest_fd);

    printf("File copied successfully.\n");

    return 0;
}





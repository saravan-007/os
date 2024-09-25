#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid, ppid;
    pid = fork();

    if (pid == 0) {
        printf("Child Process:\n");
        printf("Process ID (PID): %d\n", getpid());
        printf("Parent Process ID (PPID): %d\n", getppid());
    } else if (pid > 0) {
        printf("Parent Process:\n");
        printf("Process ID (PID): %d\n", getpid());
        printf("Parent Process ID (PPID): %d\n", getppid());
    } else {
        perror("fork");
        return 1;
    }

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <Windows.h>

int main() {
    HANDLE hPipe;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    CHAR pipeName[] = "\\\\.\\pipe\\myPipe";
    CHAR buffer[256];

    // Create pipe
    hPipe = CreateNamedPipe(
        pipeName,
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
        1,
        1024,
        1024,
        300,
        NULL
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("CreateNamedPipe failed with error %d\n", GetLastError());
        return 1;
    }

    // Create child process
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(NULL, "child_process.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        printf("CreateProcess failed with error %d\n", GetLastError());
        return 1;
    }

    // Send message to child process
    CHAR message[] = "Hello from parent process!";
    WriteFile(hPipe, message, strlen(message) + 1, NULL, NULL);

    // Receive response from child process
    ReadFile(hPipe, buffer, 256, NULL, NULL);
    printf("Parent process received response: %s\n", buffer);

    // Close handles
    CloseHandle(hPipe);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}



Child process code (child_process.exe):



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

int main() {
    HANDLE hPipe;
    CHAR pipeName[] = "\\\\.\\pipe\\myPipe";
    CHAR buffer[256];

    // Connect to pipe
    hPipe = CreateFile(pipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("CreateFile failed with error %d\n", GetLastError());
        return 1;
    }

    // Receive message from parent process
    ReadFile(hPipe, buffer, 256, NULL, NULL);
    printf("Child process received message: %s\n", buffer);

    // Send response back to parent process
    CHAR message[] = "Hello from child process!";
    WriteFile(hPipe, message, strlen(message) + 1, NULL, NULL);

    // Close handle
    CloseHandle(hPipe);

    return 0;
}



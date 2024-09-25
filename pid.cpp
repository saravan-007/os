#include <stdio.h>
#include <unistd.h>

int main() {
   printf("parent process:%d\n",getpid());
   printf("child process:%d\n",getpid());
   return 0;
}

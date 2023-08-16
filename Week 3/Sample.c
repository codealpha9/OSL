#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int status;
    pid_t pid;

    pid = fork();

    if (pid == -1) {
        printf("\nERROR child not created");
    } else if (pid == 0) { /* child process */
        printf("\nI'm the child!\n");
        exit(0);
    } else { /* parent process */
        wait(&status);
        printf("\nI'm the parent!\n");
        printf("Child returned: %d\n", status);
    }

    return 0;
}

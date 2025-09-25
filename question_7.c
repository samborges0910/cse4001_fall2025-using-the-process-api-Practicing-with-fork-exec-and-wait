#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("Parent (pid:%d) starting\n", (int)getpid());

    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child process
        printf("Child (pid:%d) running\n", (int)getpid());
        close(STDOUT_FILENO); //closing the standard output file descriptor
        printf("Child (pid:%d) trying to print after closing stdout\n", (int)getpid());
        exit(0);
    } else { // parent process
        int status;
        waitpid(rc, &status, 0);
        printf("Parent (pid:%d) done\n", (int)getpid());
    }

    return 0;
}

//calling STDOUT() frees up the descriptor and therefore the child wont be able to print anything on the screen
//after the the descriptor closes.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipefd[2]; // creating pipe
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    int rc = fork();

    if (rc < 0) { //if fork fails
        perror("fork failed");
        exit(1);
    }
    else if (rc == 0) { // child
        printf("hello\n");        // child prints hello first
        fflush(stdout);           // ensure it's printed immediately
        write(pipefd[1], "x", 1); // signal parent
        close(pipefd[1]);
        exit(0);
    }
    else { // parent
        char buf;
        read(pipefd[0], &buf, 1); // wait for child signal
        printf("goodbye\n");
        close(pipefd[0]);
    }

    return 0;
}

//using pipe ensures that the child can connect with the parent, so the parent waits for the childs signal
//before printing.

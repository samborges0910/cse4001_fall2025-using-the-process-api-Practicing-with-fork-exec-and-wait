#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("hello (pid:%d)\n", (int)getpid());

    int rc = fork();   // create a child process

    if (rc < 0) { // if forked fails
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child process
        printf("child (pid:%d)\n", (int)getpid());
        printf("child is done\n");
    } else { // parent process
        int rc_wait = wait(NULL);  // wait for child
        printf("parent of %d (rc_wait:%d) (pid:%d)\n",
               rc, rc_wait, (int)getpid());
    }

    return 0;
}

//the wait() command is important because it doesn't matter if the parent runs first, it will wait for the child
//to finish running, then wait returns and the parent prints the message. If wait() is inside the child, it will
// fail because the child doesn't have child of it's own to wait for.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("Parent (pid:%d) starting\n", (int)getpid());

    int rc = fork();

    if (rc < 0) { // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child process
        printf("Child (pid:%d) running\n", (int)getpid());
        printf("Child (pid:%d) done\n", (int)getpid());
        exit(0); // terminate child
    } else { // parent process
        int status;
        int rc_wait = waitpid(rc, &status, 0); // using waitpid
        printf("Parent: waitpid() returned %d (child pid), status=%d (pid:%d)\n",
               rc_wait, status, (int)getpid());
    }

    return 0;
}

//waitpid() will be more useful if the parent wants to wait for a specific child, (like if there is more then 1 child)
// and it will also give the exit status of the child.

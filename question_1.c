#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int x = 100;  // accessing the variable

    printf("Before fork: x=%d (pid:%d)\n", x, (int)getpid());

    int rc = fork();

    if (rc < 0) { //if the fork fails
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0) {  // the child process
        printf("Child: initially x=%d (pid:%d)\n", x, (int)getpid());
        x += 50;
        printf("Child: after change x=%d (pid:%d)\n", x, (int)getpid());
    }
    else {  // the parent process
        int rc_wait = wait(NULL);
        printf("Parent: initially x=%d (pid:%d) (wait returned %d)\n", x, (int)getpid(), rc_wait);
        x -= 30;
        printf("Parent: after change x=%d (pid:%d)\n", x, (int)getpid());
    }

    return 0;
}

//The initial value of the variable is 100, and in the child process it adds 50, meaning that the final 
//process is 150. After the fork, the child gets a copy of the parents memory, so the change in one process doesn't 
//change the other, meaning the child and parent process can have different values(150 and 70). 

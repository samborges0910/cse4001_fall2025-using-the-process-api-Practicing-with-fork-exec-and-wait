#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int x = 100;

    printf("Before fork: x=%d (pid:%d)\n", x, (int)getpid());

    // creating a file (output.txt) to show that it inherits the value from child and parent
    int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open failed");
        exit(1);
    }

    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0) { //the child process
        printf("Child: initially x=%d (pid:%d)\n", x, getpid());
        x += 50;
        printf("Child: after change x=%d (pid:%d)\n", x, getpid());

        // prints in output.txt
        dprintf(fd, "Child writes: x=%d (pid:%d)\n", x, getpid());
        close(fd);
        exit(0);
    }
    else {  //the parent process
        int rc_wait = wait(NULL);  // wait for child
        printf("Parent: initially x=%d (pid:%d) (wait returned %d)\n", x, getpid(), rc_wait);
        x -= 30;
        printf("Parent: after change x=%d (pid:%d)\n", x, getpid());

        // prints in output.txt
        dprintf(fd, "Parent writes: x=%d (pid:%d)\n", x, getpid());
        close(fd);
    }

    return 0;
}

//Both the child and parent access the file descriptor returned by open(). If the fork is called after the open file
//description is created, both the parent and child will be sharing the same open file. If they write at the same time, 
//they can interleave at the byte level or overlap, depending on timing, causing incorrect text.

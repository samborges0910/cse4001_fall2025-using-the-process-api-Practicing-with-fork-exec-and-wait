#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int rc = fork();

    if (rc < 0) {  // fork failed
        perror("fork failed");
        exit(1);
    }
    else if (rc == 0) {  // the child process
        printf("Child (pid:%d) running /bin/ls using execl...\n", getpid());
        fflush(stdout);

        // Using execl:
         execl("/bin/ls", "ls", "-l", NULL);

        // Using execlp (searches PATH):
        // execlp("ls", "ls", "-l", NULL);

        // Using execv:
        // char *args[] = {"ls", "-l", NULL};
        // execv("/bin/ls", args);

        // Using execvp (searches PATH):
        //char *args[] = {"ls", "-l", NULL};
        //execvp("ls", args);

        // Using execvpe (searches PATH + environment)
        // char *env2[] = {"MYVAR=456", NULL};
        // execvpe("ls", args, env2);

        // If exec fails:
        perror("exec failed");
        exit(1);
    }
    else {  // parent process
        int rc_wait = wait(NULL);  // wait for child to finish
        printf("Parent (pid:%d) finished waiting (child rc_wait=%d)\n", getpid(), rc_wait);
    }

    return 0;
}

//the exec() call that should be used depends on the case. Some of them are used preferably to search for paths, 
//while others are better to simulate different enviroments.

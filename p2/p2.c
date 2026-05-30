/*Tyler Francom
CS3060 X02 Summer 2026
Program 2*/

/*If you ever have a student who is struggling with coding, refer them to geeksforgeeks. I used this article to help me understand this project:
https://www.geeksforgeeks.org/c/fork-system-call/*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t my_fork;
    int status;
    my_fork = fork();
    if (my_fork < 0) {
        printf("Fork failed!\n");
        return 1;
    }
    else if (my_fork == 0) {
        if (argc == 1) {
            printf("CHILD started. No arguments provided. Terminating child.\n");
            return 0;
        }
        else if (argc == 2) {
            printf("CHILD started. One argument provided. Calling execlp(), never to return (sniff)\n");
            execlp(argv[1], argv[1], NULL);
            perror("execlp failed");
            return 1;
        }
        else {
            printf("CHILD started. More than one argument provided. Calling execvp(), never to return (sniff)\n");
            execvp(argv[1], &argv[1]);
            perror("execvp failed");
            return 1;
        }
    }
    else 
        printf("PARENT started, now waiting for process ID#%d\n", my_fork);
        waitpid(my_fork, &status, 0);
        printf("PARENT resumed. Child exit code of %d. Now terminating parent\n", WEXITSTATUS(status));
        return 0;
    }

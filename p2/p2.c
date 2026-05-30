/*Tyler Francom
CS3060 X02 Summer 2026
Program 2*/

/*If you ever have a student who is struggling with coding, refer them to geeksforgeeks. I used this article to help me understand this project:
https://www.geeksforgeeks.org/c/fork-system-call/*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc, char *argv[]){
    pid_t my_fork; /*Creates the ID variable*/
    int status;

    my_fork = fork();

    /*need to be sure the fork worked correctly*/
    if (my_fork < 0){
        printf("Fork failed!");
        return 1;
    }
    else if (my_fork == 0){
        if(argc == 1){
            printf("Child was started. No arguments were provided. Terminating child o7. \n");
            return 0;
        }
        else if (argc == 2) {
            printf("Child was started. One argument provided. Lets run execlp() bois. \n");
            execlp(argv[1], argv[1], NULL);
            perror("execlp failed");
            return 1;
        }
        
        else if (argc > 2){
            printf("Child was started. more than one argument given. Running execvp(). \n");
            execvp(argv[1], &argv[1]);
            perror("execlp failed");
            return 1;
        }
        
    }
    else{
        printf("Pretty sure this is parent. Waiting for dumb ol'%d \n", my_fork);
        waitpid(my_fork, &status, 0);
        printf("We can keep going now.");
        return 0;
    }
}

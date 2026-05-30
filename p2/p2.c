/*Tyler Francom
CS3060 X02 Summer 2026
Program 2*/

/*If you ever have a student who is struggling with coding, refer them to geeksforgeeks. I used this article to help me understand this project:
https://www.geeksforgeeks.org/c/fork-system-call/*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
    pid_t my_fork; /*Creates the ID variable*/

    my_fork = fork();

    /*need to be sure the fork worked correctly*/
    if (my_fork < 0){
        printf("Fork failed!");
        return 1;
    }
    else if (my_fork == 0){
        printf("I am your secret child. My ID is %d \n", getpid());
        return 1;
    }
    else{
        printf("Pretty sure this is parent. Waiting for dumb ol'%d \n", my_fork);
        return 1;
    }
}

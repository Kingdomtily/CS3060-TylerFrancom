/*Tyler Francom
CS3060 X02 Summer 2026
Program 3*/

#include <pthread.h>
#include <stdio.h>


void factor(number){
    while (number%2 ==0){
        printf("%d", 2);
        number = number/2;
    }
    for (int i =3; i*i <=n; i = i+2){
        while (n % i == 0){
            printf("%d", i);
            number = number/i;
        }
    }
    if (n > 2)
}

int main(){
    int test = 315;
    factor(test);
    return 0;
}
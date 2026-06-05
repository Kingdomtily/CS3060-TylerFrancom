/*Tyler Francom
CS3060 X02 Summer 2026
Program 3*/

#include <pthread.h>
#include <stdio.h>


void getFactors(int number){
    while (number%2 ==0){
        printf("%d ", 2);
        number = number/2;
    }
    for (int i =3; i*i <=number; i = i+2){
        while (number % i == 0){
            printf("%d ", i);
            number = number/i;
        }
    }
    if (number > 2);
    printf("%d ", number);
}

int main(){
    int test = 315;
    getFactors(test);
    return 0;
}
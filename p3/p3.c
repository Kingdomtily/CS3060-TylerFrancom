/*Tyler Francom
CS3060 X02 Summer 2026
Program 3*/

#include <pthread.h>
#include <stdio.h>

typedef struct {
    int original;
    int factors[64];
    int count;
} FactorResult;

void getFactors(int number, FactorResult *result){
    while (number%2 ==0){
        result->factors[result->count++] = 2;
        number = number/2;
    }
    for (int i =3; i*i <=number; i = i+2){
        while (number % i == 0){
            result->factors[result->count++] = i;
            number = number/i;
        }
    }
    if (number > 2)
    result->factors[result->count++] = number;
}

int main(){
    int test = 315;
    getFactors(test);
    return 0;
}
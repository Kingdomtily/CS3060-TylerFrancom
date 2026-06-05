/*Tyler Francom
CS3060 X02 Summer 2026
Program 3*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int original;
    int factors[64];
    int count;
} FactorResult;

void getFactors(int number, FactorResult *result){
    result->original = number;
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

void *factorThread(void *arg)
{
    int number = *(int *)arg;

    FactorResult *result =
        malloc(sizeof(FactorResult));

    result->count = 0;

    getFactors(number, result);

    return result;
}

int main() {
    pthread_t threadid;

    int test = 315;

    pthread_create(
        &threadid,
        NULL,
        factorThread,
        &test
    );

    FactorResult *result;

    pthread_join(
        threadid,
        (void **)&result
    );

    printf("%d:", result->original);

    for (int i = 0; i < result->count; i++) {
        printf(" %d", result->factors[i]);
    }

    printf("\n");

    free(result);

    return 0;
}
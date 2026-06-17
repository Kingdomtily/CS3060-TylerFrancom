/*Tyler Francom
CS3060 X02 Summer 2026
Program 3*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ITEMS 1000

int numberBuffer[MAX_ITEMS];

int numInBuffer = 0;
int mainDone = 0;

pthread_mutex_t buffer1Mutex = PTHREAD_MUTEX_INITIALIZER;

FactorResult *resultBuffer[MAX_ITEMS];

int resultCount = 0;
int producerDone = 0;

pthread_mutex_t buffer2Mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int original;
    int factors[64];
    int count;
} FactorResult;

void getFactors(int number, FactorResult *result){
    result->original = number;
    result->count =0;
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

int main(int argc, char *argv[]) {
    if (argc < 2) {
    printf("Usage:./p3 <number to factor>...\n");
    return 1;
    }
    int count = argc - 1;
    pthread_t threads[count];
    int values[count];
    for (int i = 0; i < count; i++) {
    values[i] = atoi(argv[i + 1]);
    pthread_create(
        &threads[i],
        NULL,
        factorThread,
        &values[i]
    );
}
    for (int i = 0; i < count; i++) {
    FactorResult *result;
    pthread_join(
        threads[i],
        (void **)&result
    );
    printf("%d:", result->original);
    for (int j = 0; j < result->count; j++) {
        printf(" %d", result->factors[j]);
    }
    printf("\n");
    free(result);
    }
    return 0;
}
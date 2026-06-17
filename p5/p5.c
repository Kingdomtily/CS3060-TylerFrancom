/*Tyler Francom
CS3060 X02 Summer 2026
Program 3*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ITEMS 1000

typedef struct {
    int original;
    int factors[64];
    int count;
} FactorResult;

int numberBuffer[MAX_ITEMS];

int numInBuffer = 0;
int mainDone = 0;

pthread_mutex_t buffer1Mutex = PTHREAD_MUTEX_INITIALIZER;

FactorResult *resultBuffer[MAX_ITEMS];

int resultCount = 0;
int producerDone = 0;

pthread_mutex_t buffer2Mutex = PTHREAD_MUTEX_INITIALIZER;


void *producer(void *arg)
{
    while (1)
    {
        int number;
        pthread_mutex_lock(&buffer1Mutex);
        if (numInBuffer > 0)
        {
            number = numberBuffer[0];

            for (int i = 1; i < numInBuffer; i++){
                numberBuffer[i - 1] = numberBuffer[i];}
            numInBuffer--;
            pthread_mutex_unlock(&buffer1Mutex);
        }
        else
        {
            if (mainDone)
            {
                pthread_mutex_unlock(&buffer1Mutex);
                break;
            }

            pthread_mutex_unlock(&buffer1Mutex);
            continue;
        }

        FactorResult *result =
            malloc(sizeof(FactorResult));
        getFactors(number, result);
        pthread_mutex_lock(&buffer2Mutex);
        resultBuffer[resultCount++] = result;
        pthread_mutex_unlock(&buffer2Mutex);
    }
    producerDone = 1;
    return NULL;
}

void *consumer(void *arg)
{
    while (1)
    {
        FactorResult *result;
        pthread_mutex_lock(&buffer2Mutex);
        if (resultCount > 0)
        {
            result = resultBuffer[0];
            for (int i = 1; i < resultCount; i++)
                resultBuffer[i - 1] = resultBuffer[i];
            resultCount--;
            pthread_mutex_unlock(&buffer2Mutex);
        }
        else
        {
            if (producerDone)
            {
                pthread_mutex_unlock(&buffer2Mutex);
                break;
            }
            pthread_mutex_unlock(&buffer2Mutex);
            continue;
        }
        printf("%d:", result->original);
        for (int i = 0; i < result->count; i++)
            printf(" %d", result->factors[i]);
        printf("\n");
        free(result);
    }
    return NULL;
}

pthread_t producerThread;
pthread_t consumerThread;

pthread_create(
    &producerThread,
    NULL,
    producer,
    NULL
);
pthread_create(
    &consumerThread,
    NULL,
    consumer,
    NULL
);


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
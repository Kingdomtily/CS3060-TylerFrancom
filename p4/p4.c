/*Tyler Francom
CS3060 X02 Summer 2026
Program 4*/

#include <stdio.h>

#define MAX_PROCESSES 100

int arrivalTime[MAX_PROCESSES];
int burstTime[MAX_PROCESSES];
int processCount = 0;
int main(void){
while(scanf("%d%d", &arrivalTime[processCount], &burstTime[processCount]) == 2)
{
    processCount++;
}

printf("Read %d processes\n", processCount);
return 0;
}
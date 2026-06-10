/*Tyler Francom
CS3060 X02 Summer 2026
Program 4*/

#include <stdio.h>

#define MAX_PROCESSES 100

int arrivalTime[MAX_PROCESSES];
int burstTime[MAX_PROCESSES];
int processCount = 0;

void fcfs(int arrivalTime[], int burstTime[], int n){
    int clock = 0;
    int firstRun[MAX_PROCESSES];
    int finish[MAX_PROCESSES];
    double responseTime = 0;
    double turnaroundTime = 0;
    double waitTime = 0;

        for(int i = 0; i < n; i++){
        firstRun[i] = -1;
    }
    for(int i = 0; i < n; i++){
        if(clock < arrivalTime[i]){
            clock = arrivalTime[i];
        }
        firstRun[i] = clock;
        clock += burstTime[i];
        finish[i] = clock;
    }
    for(int i = 0; i < n; i++)
{
    responseTime = firstRun[i] - arrivalTime[i];
    turnaroundTime = finish[i] - arrivalTime[i];
    waitTime = turnaroundTime - burstTime[i];
}
}
int main(void){
while(scanf("%d%d", &arrivalTime[processCount], &burstTime[processCount]) == 2)
{
    processCount++;
}


fcfs(arrivalTime, burstTime, processCount);
printf("First come, First serve \n");
printf("Shortest Job First \n");
printf("Shortest Remaining Time First\n");
printf("Rount Robin with Time Quantum of 100 \n");
return 0;
}
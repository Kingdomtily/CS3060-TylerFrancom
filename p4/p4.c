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
    double totalResponse = 0;
    double totalTurnaround = 0;
    double totalWait = 0;

    for(int i = 0; i < n; i++){
        firstRun[i] = -1;
    }

    for(int i = 0; i < n; i++)
    {
        if(clock < arrivalTime[i]){
            clock = arrivalTime[i];
        }
        firstRun[i] = clock;
        clock += burstTime[i];
        finish[i] = clock;
    }

    for(int i = 0; i < n; i++){
        int responseTime =
            firstRun[i] - arrivalTime[i];
        int turnaroundTime =
            finish[i] - arrivalTime[i];
        int waitTime =
            turnaroundTime - burstTime[i];
        totalResponse += responseTime;
        totalTurnaround += turnaroundTime;
        totalWait += waitTime;
    }
    printf("Avg. Resp.:%.2f, Avg. T.A.:%.2f, Avg. Wait:%.2f\n",
        totalResponse / n,
        totalTurnaround / n,
        totalWait / n
    );
}


int main(void){
while(scanf("%d%d", &arrivalTime[processCount], &burstTime[processCount]) == 2)
{
    processCount++;
}

printf("First come, First serve \n");
fcfs(arrivalTime, burstTime, processCount);
printf("Shortest Job First \n");
printf("Shortest Remaining Time First\n");
printf("Rount Robin with Time Quantum of 100 \n");
return 0;
}
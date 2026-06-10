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

void sjf(int arrivalTime[], int burstTime[], int n){
    int completed[MAX_PROCESSES];
    int firstRun[MAX_PROCESSES];
    int finish[MAX_PROCESSES];

    int done = 0;
    int clock = 0;

    double totalResponse = 0;
    double totalTurnaround = 0;
    double totalWait = 0;

    for (int i = 0; i<n; i++){
        completed[i] = 0;
        firstRun[i] = -1;
    }
    while(done < n)
    {
        int chosen = -1;
        for(int i = 0; i<n; i++)
        {
            if(arrivalTime[i] <= clock && completed[i] == 0)
            {
                if(chosen == -1 ||
                burstTime[i] < burstTime[chosen])
                {
                chosen = i;
                }
            }
        }
        if(chosen == -1)
        {
            int nextArrival = -1;
            for(int i = 0; i < n; i++)
            {
                if(completed[i] == 0)
                {
                    if(nextArrival == -1 ||
                       arrivalTime[i] < nextArrival)
                    {
                        nextArrival = arrivalTime[i];
                    }
                }
            }
            clock = nextArrival;
            continue;
        }
        if(firstRun[chosen] == -1)
        {
            firstRun[chosen] = clock;
        }
        clock += burstTime[chosen];
        finish[chosen] = clock;
        completed[chosen] = 1;
        done++;
    }
    for(int i = 0; i < n; i++)
    {
        int response = firstRun[i] - arrivalTime[i];
        int turnaround = finish[i] - arrivalTime[i];
        int wait = turnaround - burstTime[i];

        totalResponse += response;
        totalTurnaround += turnaround;
        totalWait += wait;
    }
    printf("Avg. Resp.:%.2f, Avg. T.A.:%.2f, Avg. Wait:%.2f\n",
           totalResponse / n,
           totalTurnaround / n,
           totalWait / n);
}


void srtf(int arrivalTime[], int burstTime[], int n)
{
    int remaining[MAX_PROCESSES];
    int firstRun[MAX_PROCESSES];
    int finish[MAX_PROCESSES];

    int completed = 0;
    int clock = 0;

    double totalResponse = 0;
    double totalTurnaround = 0;
    double totalWait = 0;

    for(int i = 0; i < n; i++)
    {
        remaining[i] = burstTime[i];
        firstRun[i] = -1;
        finish[i] = 0;
    }
    while(completed < n)
    {
        int chosen = -1;
        for(int i = 0; i < n; i++)
        {
            if(arrivalTime[i] <= clock && remaining[i] > 0)
            {
                if(chosen == -1 ||
                   remaining[i] < remaining[chosen])
                {
                    chosen = i;
                }
            }
        }
        if(chosen == -1)
        {
            int nextArrival = -1;

            for(int i = 0; i < n; i++)
            {
                if(remaining[i] > 0)
                {
                    if(nextArrival == -1 ||
                       arrivalTime[i] < nextArrival)
                    {
                        nextArrival = arrivalTime[i];
                    }
                }
            }
            clock = nextArrival;
            continue;
        }
        if(firstRun[chosen] == -1)
        {
            firstRun[chosen] = clock;
        }
        remaining[chosen]--;
        clock++;
        if(remaining[chosen] == 0)
        {
            finish[chosen] = clock;
            completed++;
        }
    }
    for(int i = 0; i < n; i++)
    {
        int response = firstRun[i] - arrivalTime[i];
        int turnaround = finish[i] - arrivalTime[i];
        int wait = turnaround - burstTime[i];

        totalResponse += response;
        totalTurnaround += turnaround;
        totalWait += wait;
    }
;
    printf("Avg. Resp.:%.2f, Avg. T.A.:%.2f, Avg. Wait:%.2f\n",
           totalResponse / n,
           totalTurnaround / n,
           totalWait / n);
}


int main(void){
while(scanf("%d%d", &arrivalTime[processCount], &burstTime[processCount]) == 2)
{
    processCount++;
}

printf("First come, First serve \n");
fcfs(arrivalTime, burstTime, processCount);
printf("Shortest Job First \n");
sjf(arrivalTime, burstTime, processCount);
printf("Shortest Remaining Time First\n");
srtf(arrivalTime, burstTime, processCount);
printf("Rount Robin with Time Quantum of 100 \n");
return 0;
}
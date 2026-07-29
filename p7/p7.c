#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void copyArray(const int source[], int destination[], int count)
{
    for (int i=0; i< count; i++)
    {
        destination[i] = source[i];
    }
}

int fcfs(int requests[], int count);
int sstf(int requests[], int count);
int look(int requests[], int count);
int clook(int requests[], int count);

int main(void)
{
    return 0;
}
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

void sortArrayy(int array[], int count)
{
    for (int i=0; i < count -1; i++)
    {
        int smallestIndex = i;
        for (int j = i + 1; j < count; j++)
        {
            if (array[j] < array[smallestIndex])
            {
                smallestIndex = j;
            }
        }
        if (smallestIndex != i)
        {
            int temp = array[i];
            array[i] = array[smallestIndex];
            array[smallestIndex] = temp;
        }
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
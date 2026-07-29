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

int fcfs(const int requests[], int count)
{
    int totalSeek = 0;
    int currentPosition = requests[0];

    for (int i = 1; i < count; i++)
    {
        totalSeek += abs(currentPosition - requests[i]);
        currentPosition = requests[i];
    }

    return totalSeek;
}

int sstf(const int requests[], int count)
{
    int used[MAX_REQUESTS] = {0};
    int totalSeek = 0;
    int currentPosition = requests[0];
    used[0] = 1;
    for (int completed = 1; completed < count; completed++)
    {
        int bestIndex = -1;
        int shortestDistance = 0;

        for (int i = 1; i < count; i++)
        {
            if (used[i] == 0)
            {
                int distance =
                    abs(currentPosition - requests[i]);

                if (bestIndex == -1 ||
                    distance < shortestDistance)
                {
                    bestIndex = i;
                    shortestDistance = distance;
                }
            }
        }
        totalSeek += shortestDistance;
        currentPosition = requests[bestIndex];
        used[bestIndex] = 1;
    }
    return totalSeek;
}

int look(const int requests[], int count)
{
    int sorted[MAX_REQUESTS];
    int requestCount = count - 1;
    int currentPosition = requests[0];
    int totalSeek = 0;
    int firstHigher = requestCount;
    copyArray(requests + 1, sorted, requestCount);
    sortArray(sorted, requestCount);
    for (int i = 0; i < requestCount; i++)
    {
        if (sorted[i] >= currentPosition)
        {
            firstHigher = i;
            break;
        }
    }
}

int clook(const int requests[], int count)
{
    int sorted[MAX_REQUESTS];
    int requestCount = count - 1;
    int currentPosition = requests[0];
    int totalSeek = 0;
    int firstHigher = requestCount;
    copyArray(requests + 1, sorted, requestCount);
    sortArray(sorted, requestCount);
    for (int i = 0; i < requestCount; i++)
    {
        if (sorted[i] >= currentPosition)
        {
            firstHigher = i;
            break;
        }
    }
    for (int i = firstHigher; i < requestCount; i++)
    {
        totalSeek += abs(currentPosition - sorted[i]);
        currentPosition = sorted[i];
    }
    for (int i = 0; i < firstHigher; i++)
    {
        totalSeek += abs(currentPosition - sorted[i]);
        currentPosition = sorted[i];
    }
    return totalSeek;
}
int main(void)
{
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_REQUESTS 100
#define UP 1
#define DOWN -1

void copyArray(const int source[], int destination[], int count)
{
    for (int i = 0; i < count; i++)
    {
        destination[i] = source[i];
    }
}

void sortArray(int array[], int count)
{
    for (int i = 0; i < count - 1; i++)
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

int sstf(const int requests[], int count, int randomTies)
{
    int used[MAX_REQUESTS] = {0};
    int totalSeek = 0;
    int currentPosition = requests[0];
    used[0] = 1;
    for (int completed = 1; completed < count; completed++)
    {
        int bestIndex = -1;
        int shortestDistance = 0;
        int tieCount = 0;
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
                    tieCount = 1;
                }
                else if (distance == shortestDistance &&
                         randomTies)
                {
                    tieCount++;

                    if (rand() % tieCount == 0)
                    {
                        bestIndex = i;
                    }
                }
            }
        }
        if (bestIndex != -1)
        {
            totalSeek +=
                abs(currentPosition - requests[bestIndex]);
            currentPosition = requests[bestIndex];
            used[bestIndex] = 1;
        }
    }
    return totalSeek;
}

int look(const int requests[], int count, int direction)
{
    int sorted[MAX_REQUESTS];
    int requestCount = count - 1;
    int currentPosition = requests[0];
    int totalSeek = 0;
    if (requestCount <= 0)
    {
        return 0;
    }
    copyArray(requests + 1, sorted, requestCount);
    sortArray(sorted, requestCount);
    if (direction == UP)
    {
        int firstHigher = requestCount;
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
            totalSeek +=
                abs(currentPosition - sorted[i]);

            currentPosition = sorted[i];
        }
        for (int i = firstHigher - 1; i >= 0; i--)
        {
            totalSeek +=
                abs(currentPosition - sorted[i]);

            currentPosition = sorted[i];
        }
    }
    else
    {
        int firstGreater = requestCount;
        for (int i = 0; i < requestCount; i++)
        {
            if (sorted[i] > currentPosition)
            {
                firstGreater = i;
                break;
            }
        }
        for (int i = firstGreater - 1; i >= 0; i--)
        {
            totalSeek +=
                abs(currentPosition - sorted[i]);
            currentPosition = sorted[i];
        }
        for (int i = firstGreater; i < requestCount; i++)
        {
            totalSeek +=
                abs(currentPosition - sorted[i]);
            currentPosition = sorted[i];
        }
    }
    return totalSeek;
}

int clook(const int requests[], int count, int direction)
{
    int sorted[MAX_REQUESTS];
    int requestCount = count - 1;
    int currentPosition = requests[0];
    int totalSeek = 0;
    if (requestCount <= 0)
    {
        return 0;
    }
    copyArray(requests + 1, sorted, requestCount);
    sortArray(sorted, requestCount);

    if (direction == UP)
    {
        int firstHigher = requestCount;
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
            totalSeek +=
                abs(currentPosition - sorted[i]);

            currentPosition = sorted[i];
        }
        for (int i = 0; i < firstHigher; i++)
        {
            totalSeek +=
                abs(currentPosition - sorted[i]);
            currentPosition = sorted[i];
        }
    }
    else
    {
        int firstGreater = requestCount;
        for (int i = 0; i < requestCount; i++)
        {
            if (sorted[i] > currentPosition)
            {
                firstGreater = i;
                break;
            }
        }
        for (int i = firstGreater - 1; i >= 0; i--)
        {
            totalSeek +=
                abs(currentPosition - sorted[i]);

            currentPosition = sorted[i];
        }
        for (int i = requestCount - 1;
             i >= firstGreater;
             i--)
        {
            totalSeek +=
                abs(currentPosition - sorted[i]);
            currentPosition = sorted[i];
        }
    }

    return totalSeek;
}

void printUsage(const char programName[])
{
    fprintf(stderr,
            "Usage: %s [-r] [-u | -d]\n",
            programName);
    fprintf(stderr,
            "  -r  Randomly resolve SSTF ties\n");
    fprintf(stderr,
            "  -u  Start LOOK and C-LOOK upward\n");
    fprintf(stderr,
            "  -d  Start LOOK and C-LOOK downward\n");
}

int main(int argc, char *argv[])
{
    int requests[MAX_REQUESTS];
    int count = 0;
    int randomTies = 0;
    int direction = UP;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-r") == 0)
        {
            randomTies = 1;
        }
        else if (strcmp(argv[i], "-u") == 0)
        {
            direction = UP;
        }
        else if (strcmp(argv[i], "-d") == 0)
        {
            direction = DOWN;
        }
        else if (strcmp(argv[i], "-h") == 0 ||
                 strcmp(argv[i], "--help") == 0)
        {
            printUsage(argv[0]);
            return 0;
        }
        else
        {
            fprintf(stderr,
                    "Unknown option: %s\n",
                    argv[i]);
            printUsage(argv[0]);
            return 1;
        }
    }
    if (randomTies)
    {
        srand((unsigned int)time(NULL));
    }
    while (count < MAX_REQUESTS &&
           scanf("%d", &requests[count]) == 1)
    {
        count++;
    }
    if (count == 0)
    {
        fprintf(stderr,
                "No block requests were provided.\n");
        return 1;
    }
    printf("Assignment 7: Block Access Algorithm\n");
    printf("By: Tyler Francom\n\n");
    printf("FCFS Total Seek: %d\n",
           fcfs(requests, count));
    printf("SSTF Total Seek: %d\n",
           sstf(requests, count, randomTies));
    printf("LOOK Total Seek: %d\n",
           look(requests, count, direction));
    printf("C-LOOK Total Seek: %d\n",
           clook(requests, count, direction));
    return 0;
}
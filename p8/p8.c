#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define _GNU_SOURCE

static void listDirectory(const char *directoryPath,
                          unsigned long long *totalBytes,
                          int depth)
                          {
                            {
    DIR *directory = opendir(directoryPath);

    if (directory == NULL)
    {
        perror(directoryPath);
        return;
    }

    printf("%*sdir %s\n", depth * 2, "", directoryPath);

    struct dirent *entry;

                          }
                        }

int main(int argc, char *argv[])
{
    return 0;
}
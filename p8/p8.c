#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define _GNU_SOURCE
#define MAX_DEPTH 100

if (depth >= MAX_DEPTH)
{
    fprintf(stderr,
            "Maximum directory depth reached at: %s\n",
            directoryPath);
    return;
}


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
     while ((entry = readdir(directory)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }
        char *fullPath = NULL;
        if (asprintf(&fullPath, "%s/%s",
                     directoryPath, entry->d_name) == -1)
        {
            fprintf(stderr, "Could not allocate memory for path\n");
            closedir(directory);
            exit(EXIT_FAILURE);
        }

        struct stat fileInfo;
        if (lstat(fullPath, &fileInfo) == -1)
        {
            perror(fullPath);
            free(fullPath);
            continue;
        }
        if (S_ISREG(fileInfo.st_mode))
        {
            printf("%*s%8lld:%s\n",
                   (depth + 1) * 2,
                   "",
                   (long long)fileInfo.st_size,
                   entry->d_name);
            *totalBytes += (unsigned long long)fileInfo.st_size;
        }
        else if (S_ISDIR(fileInfo.st_mode))
        {
            listDirectory(fullPath, totalBytes, depth + 1);
        }
        free(fullPath);
    }

    closedir(directory);
    }
}
                        
int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        fprintf(stderr, "Usage: %s [directory]\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char *startingDirectory;
    if (argc == 2)
    {
        startingDirectory = argv[1];
    }
    else
    {
        startingDirectory = ".";
    }
    unsigned long long totalBytes = 0;
    listDirectory(startingDirectory, &totalBytes, 0);
    printf("\nTotal file space used:%llu\n", totalBytes);
    return EXIT_SUCCESS;
}
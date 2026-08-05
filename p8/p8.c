#define _GNU_SOURCE

#include <ctype.h>
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_DEPTH 100

/*
Pseudocode:
FOR each character in the filename
    IF the character is printable and not a backslash
        print the character normally
    ELSE
        print the character using hexadecimal notation

Security lesson:
Filenames are untrusted input. Escaping unusual characters prevents a
filename containing newlines or terminal-control characters from producing
misleading output.
*/
static void printSafeName(const char *name)
{
    const unsigned char *character =
        (const unsigned char *)name;

    while (*character != '\0')
    {
        if (isprint(*character) && *character != '\\')
        {
            putchar(*character);
        }
        else
        {
            printf("\\x%02X", *character);
        }

        character++;
    }
}

/*
Pseudocode:
IF recursion_depth >= maximum_depth
    report that the directory is too deeply nested
    stop processing that branch
ELSE
    continue scanning

IF the directory cannot be opened
    report the error
    return failure

FOR each directory entry
    skip "." and ".."
    safely create the full path

    IF file information cannot be read
        report the error
        record that an error occurred
        continue to the next entry

    IF the entry is a regular file
        IF the file size is negative
            report invalid size
            record an error
        ELSE IF adding the file size would overflow
            report overflow
            record an error
        ELSE
            add the size to the total

    ELSE IF the entry is a directory
        recursively scan it

    ELSE IF the entry is a symbolic link
        skip it and report that it was skipped

RETURN whether the directory was processed successfully
*/
static int listDirectory(const char *directoryPath,
                         unsigned long long *totalBytes,
                         int depth)
{
    int errorOccurred = 0;

    /*
    Prevent a deeply nested directory tree from exhausting the
    program's call stack.
    */
    if (depth >= MAX_DEPTH)
    {
        fprintf(stderr,
                "Maximum directory depth reached at: %s\n",
                directoryPath);
        return 1;
    }

    DIR *directory = opendir(directoryPath);

    if (directory == NULL)
    {
        perror(directoryPath);
        return 1;
    }

    printf("%*sdir ", depth * 2, "");
    printSafeName(directoryPath);
    putchar('\n');

    struct dirent *entry;

    while ((entry = readdir(directory)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        char *fullPath = NULL;

        if (asprintf(&fullPath,
                     "%s/%s",
                     directoryPath,
                     entry->d_name) == -1)
        {
            fprintf(stderr,
                    "Could not allocate memory for path\n");

            closedir(directory);
            return 1;
        }

        struct stat fileInfo;

        /*
        lstat() examines a symbolic link itself rather than following it.
        This helps prevent simple symbolic-link directory loops.
        */
        if (lstat(fullPath, &fileInfo) == -1)
        {
            perror(fullPath);
            free(fullPath);
            errorOccurred = 1;
            continue;
        }

        if (S_ISREG(fileInfo.st_mode))
        {
            printf("%*s%8lld: ",
                   (depth + 1) * 2,
                   "",
                   (long long)fileInfo.st_size);

            printSafeName(entry->d_name);
            putchar('\n');

            /*
            Avoid converting an invalid negative file size into a very
            large unsigned value.
            */
            if (fileInfo.st_size < 0)
            {
                fprintf(stderr,
                        "Invalid negative file size: ");

                printSafeName(fullPath);
                fputc('\n', stderr);

                errorOccurred = 1;
            }
            else
            {
                unsigned long long fileSize =
                    (unsigned long long)fileInfo.st_size;

                /*
                Check before adding so that totalBytes cannot wrap around.
                */
                if (ULLONG_MAX - *totalBytes < fileSize)
                {
                    fprintf(stderr,
                            "Total file size overflow while processing: ");

                    printSafeName(fullPath);
                    fputc('\n', stderr);

                    errorOccurred = 1;
                }
                else
                {
                    *totalBytes += fileSize;
                }
            }
        }
        else if (S_ISDIR(fileInfo.st_mode))
        {
            if (listDirectory(fullPath,
                              totalBytes,
                              depth + 1) != 0)
            {
                errorOccurred = 1;
            }
        }
        else if (S_ISLNK(fileInfo.st_mode))
        {
            printf("%*s[symlink skipped] ",
                   (depth + 1) * 2,
                   "");

            printSafeName(entry->d_name);
            putchar('\n');
        }
        else
        {
            printf("%*s[non-regular file skipped] ",
                   (depth + 1) * 2,
                   "");

            printSafeName(entry->d_name);
            putchar('\n');
        }

        free(fullPath);
    }

    /*
    readdir() uses errno to report errors, but checking that would require
    setting errno to zero before the loop. For this version, closedir()
    failures are still detected.
    */
    if (closedir(directory) == -1)
    {
        perror("closedir");
        errorOccurred = 1;
    }

    return errorOccurred;
}

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        fprintf(stderr,
                "Usage: %s [directory]\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    const char *startingDirectory =
        argc == 2 ? argv[1] : ".";

    unsigned long long totalBytes = 0;

    int traversalResult =
        listDirectory(startingDirectory,
                      &totalBytes,
                      0);

    printf("\nTotal file space used: %llu bytes\n",
           totalBytes);

    if (traversalResult != 0)
    {
        fprintf(stderr,
                "Warning: one or more entries could not "
                "be processed successfully.\n");

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
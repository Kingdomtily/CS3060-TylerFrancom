/*Tyler Francom
CS3060 X02 Summer 2026
Program 1*/

#include <stdio.h>

int main(int argc, char *argv[]) {

    printf("Program 1 by Tyler Francom\n");

    for (int i = 0; i < argc; i++) {
        printf("Argument #%d: %s\n", i, argv[i]);
    }

    printf("Number of arguments printed: %d\n", argc);

    return 0;
}
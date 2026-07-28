#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <hexadecimal address>\n", argv[0]);
        return 1;
    }
    unsigned long logical_addr = strtol(argv[1], NULL, 16);
    unsigned long page_index = logical_addr >> 12;
    unsigned long offset = logical_addr & 0xFFF;
    printf("Logical Addr:0x%08lX - Page Index:0x%08lX - Offset:0x%08lX\n",
           logical_addr, page_index, offset);

    return 0;
}
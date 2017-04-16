#include <stdint.h>

void printf(const char *str)
{
    uint16_t *videoMemory = (uint16_t*)0xb8000;
    int i;

    for(i = 0; *str != '\0'; i++, str++)
        *(videoMemory + i) = (*(videoMemory + i) & 0xFF00) |  *str;
}

void kernelMain(void *multiboot, unsigned int magicNumber)
{
    printf("Zinux");

    while(1);
}

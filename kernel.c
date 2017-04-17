#include <stdint.h>

#include "vga.h"
#include "tty.h"

void printf(const char *str)
{
    uint16_t *videoMemory = (uint16_t*)0xB8000;
    int i;

    for(i = 0; *str != '\0'; i++, str++)
        *(videoMemory + i) = (*(videoMemory + i) & 0xFF00) |  *str;
}

void kernelMain(void *multiboot, uint32_t magicNumber)
{
    //printf("Zinux: Zi's unix clone");
    //TTY_init();
    //TTY_changeColor(COLOR_BLACK, COLOR_RED);
    //printf("Zinux");

    TTY_init();
    TTY_changeColor(COLOR_BLACK, COLOR_RED);
    TTY_setColor(COLOR_BLACK, COLOR_CYAN);
    TTY_puts("Zinux\n\n");
    TTY_setColor(COLOR_BLACK, COLOR_GREEN);
    TTY_puts("Zinux:\t");
    TTY_setColor(COLOR_BLACK, COLOR_RED);
    TTY_puts("Zi's unix clone");

    while(1);
}

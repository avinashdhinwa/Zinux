#include <stdint.h>

#include "vga.h"
#include "tty.h"
#include "gdt.h"
#include "idt.h"
#include "irq.h"

void kernelMain(void *multiboot, uint32_t magicNumber)
{
    TTY_init();

    GDT_init();
    IDT_init();
    IRQ_init();
    IRQ_enable();

    //printf("Zinux: Zi's unix clone");
    //TTY_init();
    //TTY_changeColor(COLOR_BLACK, COLOR_RED);
    //printf("Zinux");

    TTY_changeColor(COLOR_BLACK, COLOR_RED);
    TTY_setColor(COLOR_BLACK, COLOR_CYAN);
    TTY_puts("Zinux\n\n");
    TTY_setColor(COLOR_BLACK, COLOR_GREEN);
    TTY_puts("Zinux:\t");
    TTY_setColor(COLOR_BLACK, COLOR_RED);
    TTY_puts("Zi's unix clone\n\n");

    TTY_setColor(COLOR_BLACK, COLOR_RED);

    while(1) asm("hlt");
}

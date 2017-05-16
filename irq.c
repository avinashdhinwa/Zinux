#include "irq.h"

#include "port.h"
#include "tty.h"

uint32_t IRQHandler(uint8_t irq, uint32_t esp)
{
    TTY_puts("INTERRUPT");

    return esp;
}

void IRQ_init(void)
{
    /* Initialize PIC */
    outb(PORT_PIC_MASTER_A, 0x11);
    outb(PORT_PIC_SLAVE_A, 0x11);

    /* Set offset in IDT */
    outb(PORT_PIC_MASTER_B, 0x20);
    outb(PORT_PIC_SLAVE_B, 0x28);

    /* Master/Slave communication setup */
    outb(PORT_PIC_MASTER_B, 0x04);
    outb(PORT_PIC_SLAVE_B, 0x02);

    //outb(PORT_PIC_MASTER_B, 0x05);  // Set as Master
    //outb(PORT_PIC_SLAVE_B, 0x01);   // Set as Slave

    outb(PORT_PIC_MASTER_B, 0x01);
    outb(PORT_PIC_SLAVE_B, 0x01);
    outb(PORT_PIC_MASTER_B, 0x00);
    outb(PORT_PIC_SLAVE_B, 0x00);
}

void IRQ_enable(void)
{
    asm("sti");
}

void IRQ_disable(void)
{
    asm("cli");
}

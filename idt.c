#include "idt.h"

#include "gdt.h"
#include "irq.h"

#include "tty.h"

idt_t IDT[IDT_ENTRY_COUNT];
idt_ptr_t pIDT;

void IDT_flush(void);

void IDT_create(idt_t *idt, uint32_t address, uint16_t selector, uint8_t flags)
{
    idt->addressLo = address & 0xFFFF;
    idt->addressHi = (address << 16) & 0xFFFF;
    idt->selector = selector;
    idt->flags = flags;
    idt->reserved = 0;
}

void IDT_init(void)
{
    uint16_t codeSegment = GDT_codeSegmentSelector();
    uint8_t idtGate = 0x0E;
    //idtGate = 0x8E;

    uint32_t i;
    for(i = 0; i < IDT_ENTRY_COUNT; i++)
        IDT_create(&IDT[i], (uint32_t)IRQHandlerIgnore, codeSegment, idtGate);

    IDT_create(&IDT[0x20 + 0], (uint32_t)IRQHandler00, codeSegment, idtGate);
    IDT_create(&IDT[0x20 + 1], (uint32_t)IRQHandler00, codeSegment, idtGate);
    IDT_create(&IDT[0x20 + 2], (uint32_t)IRQHandler00, codeSegment, idtGate);
    IDT_create(&IDT[0x20 + 3], (uint32_t)IRQHandler00, codeSegment, idtGate);
    IDT_create(&IDT[0x20 + 4], (uint32_t)IRQHandler00, codeSegment, idtGate);
    IDT_create(&IDT[0x20 + 5], (uint32_t)IRQHandler00, codeSegment, idtGate);

    idt_ptr_t idtr;
    idtr.size = sizeof(IDT) - 1;
    idtr.address = (uint32_t)&IDT;

    IDT_flush();
}

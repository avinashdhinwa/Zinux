#ifndef __IDT_H__
#define __IDT_H__

#include <stdint.h>

typedef struct idt_s
{
    uint16_t addressLo;
    uint16_t selector;
    uint8_t reserved;
    uint8_t flags;
    uint16_t addressHi;
} __attribute__((packed)) idt_t;

typedef struct idt_ptr_s
{
    uint16_t size;
    uint32_t address;
} __attribute__((packed)) idt_ptr_t;

void IDT_create(idt_t *idt, uint32_t address, uint16_t selector, uint8_t flags);


#define IDT_ENTRY_COUNT     256

extern idt_t IDT[IDT_ENTRY_COUNT];
void IDT_init(void);

#endif // __IDT_H__

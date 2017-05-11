#include "gdt.h"

gdt_t GDT[GDT_ENTRY_COUNT];

void GDT_create(gdt_t *gdt, uint32_t base, uint32_t limit, uint8_t type)
{
    gdt->baseLo = base & 0xFFFF;
    gdt->baseHi = (base >> 16) & 0xFF;
    gdt->baseExt = (base >> 24) & 0xFF;

    gdt->limitLo = base & 0xFFFF;
    gdt->flagsLimitHi = (base >> 16) & 0x0F;
    gdt->type = type;
}

uint32_t GDT_getBase(gdt_t *gdt)
{
    return (gdt->baseExt << 24) | (gdt->baseHi << 16) | gdt->baseLo;
}

uint32_t GDT_getLimit(gdt_t *gdt)
{
    return ((gdt->flagsLimitHi & 0x0F) << 16) | gdt->limitLo;
}

void GDT_init(void)
{
    GDT_create(&GDT[GDT_ENTRY_NULL], 0, 0, 0);
    GDT_create(&GDT[GDT_ENTRY_UNUSED], 0, 0, 0);
    GDT_create(&GDT[GDT_ENTRY_CODE], 0, 6*1024*1024, 0x9A);     // ring 0 (kernel), code
    GDT_create(&GDT[GDT_ENTRY_DATA], 0, 6*1024*1024, 0x92);     // ring 0 (kernel), data

    gdt_ptr_t gdtr;
    gdtr.size = (sizeof(GDT) - 1);
    gdtr.address = &GDT;

    asm volatile("lgdt (%0)" : : "p" ((uint8_t*)&gdtr));
}

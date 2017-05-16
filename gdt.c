#include "gdt.h"

gdt_t GDT[GDT_ENTRY_COUNT];
gdt_ptr_t pGDT;

void GDT_flush();

void GDT_create(gdt_t *gdt, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    gdt->baseLo = base & 0xFFFF;
    gdt->baseHi = (base >> 16) & 0xFF;
    gdt->baseExt = (base >> 24) & 0xFF;

    gdt->limitLo = limit & 0xFFFF;
    gdt->flagsLimitHi = (limit >> 16) & 0x0F;
    gdt->flagsLimitHi |= (flags) & 0xF0;
    gdt->access = access;
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
    GDT_create(&GDT[GDT_ENTRY_NULL], 0, 0, 0, 0);
    GDT_create(&GDT[GDT_ENTRY_CODE], 0, 0xFFFFFFFF, 0x9A, 0xCF);        // ring 0 (kernel), code
    GDT_create(&GDT[GDT_ENTRY_DATA], 0, 0xFFFFFFFF, 0x92, 0xCF);        // ring 0 (kernel), data

    pGDT.size = sizeof(GDT) - 1;
    pGDT.address = (uint32_t)&GDT;

    GDT_flush();
}

uint16_t GDT_codeSegmentSelector(void)
{
    return (uint8_t*)&GDT[GDT_ENTRY_CODE] - (uint8_t*)GDT;
}

uint16_t GDT_dataSegmentSelector(void)
{
    return (uint8_t*)&GDT[GDT_ENTRY_DATA] - (uint8_t*)GDT;
}

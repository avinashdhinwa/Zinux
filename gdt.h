#ifndef __GDT_H__
#define __GDT_H__

#include <stdint.h>

typedef struct gdt_s
{
    uint16_t limitLo;
    uint16_t baseLo;
    uint8_t baseHi;
    uint8_t access;
    uint8_t flagsLimitHi;
    uint8_t baseExt;
} __attribute__((packed)) gdt_t;

typedef struct gdt_ptr_s
{
    uint16_t size;
    uint32_t address;
} __attribute__((packed)) gdt_ptr_t;

void GDT_create(gdt_t *gdt, uint32_t base, uint32_t limit, uint8_t access, uint8_t flasg);
uint32_t GDT_getBase(gdt_t *gdt);
uint32_t GDT_getLimit(gdt_t *gdt);


#define GDT_ENTRY_NULL      0
#define GDT_ENTRY_CODE      1
#define GDT_ENTRY_DATA      2


#define GDT_ENTRY_COUNT     3

extern gdt_t GDT[GDT_ENTRY_COUNT];

void GDT_init(void);
uint16_t GDT_codeSegmentSelector(void);
uint16_t GDT_dataSegmentSelector(void);

#endif // __GDT_H__

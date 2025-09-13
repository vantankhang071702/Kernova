#include <kernel/gdt.h>

static uint64_t gdt[5];    // GDT table
static gdtr_t gdtr;        // GDTR

extern void gdt_flush(uint32_t);   // in gdt.S

uint64_t create_descriptor(uint32_t base, uint32_t limit, uint16_t flag)
{
    uint64_t descriptor;

    // High 32 bits
    descriptor  = (limit & 0x000F0000ULL);            // limit bits 19:16
    descriptor |= ((uint64_t)flag << 8) & 0x00F0FF00ULL; // flags/type
    descriptor |= ((uint64_t)(base >> 16) & 0xFF) << 16; // base 23:16
    descriptor |= ((uint64_t)(base >> 24) & 0xFF) << 24; // base 31:24

    descriptor <<= 32;

    // Low 32 bits
    descriptor |= ((uint64_t)base & 0xFFFF) << 16; // base 15:0
    descriptor |= (limit & 0xFFFF);                // limit 15:0

    return descriptor;
}

void gdt_init() 
{
    gdt[0] = create_descriptor(0, 0, 0);                       // Null
    gdt[1] = create_descriptor(0, 0x000FFFFF, GDT_CODE_PL0);   // Kernel code
    gdt[2] = create_descriptor(0, 0x000FFFFF, GDT_DATA_PL0);   // Kernel data
    gdt[3] = create_descriptor(0, 0x000FFFFF, GDT_CODE_PL3);   // User code
    gdt[4] = create_descriptor(0, 0x000FFFFF, GDT_DATA_PL3);   // User data

    gdtr.size = sizeof(gdt) - 1;
    gdtr.offset = (uint32_t)&gdt;

    gdt_flush((uint32_t)&gdtr);
}

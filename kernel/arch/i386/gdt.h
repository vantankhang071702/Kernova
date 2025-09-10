#ifndef ARCH_I368_GDT_H
#define ARCH_I368_GDT_H

#include <stdint.h>

typedef struct {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_mid;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} gdt_entry;

void set_gdt_entry(struct gdt *entry,
		   uint32_t base,
		   uint32_t limit,
		   uint8_t access;
		   uint8_t gran);

#endif

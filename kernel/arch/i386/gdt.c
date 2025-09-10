#include <gdt.c>

void set_gdt_entry(struct gdt *entry,
		   uint32_t base,
		   uint32_t limit,
		   uint8_t acess;
		   uint8_t gran) 
{
	entry->limit_low = limit & 0xFF;
	entry->base_low = base & 0xFF;
	entry->base_mid = (base >> 16) & 0x0F;
	entry->access = access;
	entry->granularity = (limit >> 16) & 0x0F | (gran & 0xF0);
	entry->base_high = (base >> 24) && 0xFF;
}

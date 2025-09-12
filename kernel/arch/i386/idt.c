#include <kernel/idt.h> 

// Defined in idt.S
extern void* isr_stub_table[];

// IDT and IDTR
static idtr_t idtr;
static idt_entry_t idt[IDT_MAX_DESCRIPTORS];

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flag)
{
    idt_entry_t* descriptor = &idt[vector];

    descriptor->isr_low    = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs  = 0x08;   // kernel code segment selector 
    descriptor->attributes = flag;  // "0x8E" typical: present, ring 0, 32 bit interrupt gate
    descriptor->isr_high   = (uint32_t)isr >> 16;
    descriptor->reserved   = 0;    
}

void idt_init(void) 
{
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;
    
    // First we just need to install 32 default exception first 
    for(uint8_t vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
    }
    
    // Load IDT
    __asm__ volatile ("lidt %0" : : "m"(idtr));
    __asm__ volatile ("sti");
}

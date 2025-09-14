#ifndef KERNEL_IDT_H
#define KERNEL_IDT_H

#include <stdint.h>

#define IDT_MAX_DESCRIPTORS 256

// IDTR structure
typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idtr_t;

// IDT entry structure
typedef struct {
    uint16_t isr_low;    // The lower 16 bits of the ISR's address
    uint16_t kernel_cs;  // The GDT segment selector that the CPU will load into CS before calling to the ISR
    uint8_t  reserved;   // Set to zero
    uint8_t  attributes; // Type and attributes, see the IDT page
    uint16_t isr_high;   // The higher 16 bits of the ISR's address   
} __attribute__((packed)) idt_entry_t;

// Function prototypes
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
void idt_init(void);

#endif // KERNEL_IDT_H

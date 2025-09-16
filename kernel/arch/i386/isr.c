#include <stdio.h>
#include <kernel/idt.h>

void isr_handler(uint32_t int_no, uint32_t err_code) {
    // TODO: hang system first, we can extend to print message later
    (void)int_no;
    (void)err_code;

    __asm__ volatile("cli; hlt");
}

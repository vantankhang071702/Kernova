#include <stdio.h>
#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>

void kernel_main(void) 
{
    gdt_init();
    idt_init();
    terminal_initialize();
}

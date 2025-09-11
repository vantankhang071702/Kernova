.intel_syntax noprefix      # allow Intel-like syntax
.global gdt_flush

gdt_flush:
    mov eax, [esp+4]        # pointer to gdt_ptr passed from C
    lgdt [eax]

    mov ax, 0x10            # Data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08, flush_cs      # far jump
flush_cs:
    ret


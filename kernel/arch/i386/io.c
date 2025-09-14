#include <kernel/io.h>

uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ __volatile__ (
        "in al, dx"
        : "=a"(ret)
        : "d"(port)
    );
    return ret;
}

void outb(uint16_t port, uint8_t val)
{
    __asm__ __volatile__ (
        "out dx, al"
        :
        : "d"(port), "al"(val)
    );
}


#ifndef ARCH_I386_IO_H
#define ARCH_I386_IO_H

#include <stdint.h>

// Read a byte to an I/O port
static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ __volatile__ (
        "in al, dx"
        : "=a"(ret)
        : "d"(port)
    );
    return ret;
}

// Write a byte to an I/O port
static inline void outb(uint16_t port, uint8_t val)
{
    __asm__ __volatile__ (
        "out dx, al"
        :
        : "d"(port), "al"(val)
    );
}

static inline void io_wait(void)
{
    outb(0x80, 0);
}

#endif // ARCH_I386_IO_H

#ifndef IO_H
#define IO_H

#include <stdint.h>

uint8_t inb(uint16_t port);
void oub(uint16_t port, uint8_t val);

#endif

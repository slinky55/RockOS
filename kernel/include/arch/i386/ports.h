#ifndef _arch_i386_ports_h
#define _arch_i386_ports_h

#include <stdint.h>

void outb(uint16_t port, uint8_t val);
void outw(uint16_t port, uint16_t val);
void outd(uint16_t port, uint32_t val);

uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
uint32_t ind(uint16_t port);

void io_wait(void);

#endif

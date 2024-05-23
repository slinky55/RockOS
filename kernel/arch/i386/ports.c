#include <arch/i386/ports.h>

void outb(uint16_t port, uint8_t val) {
  __asm__ volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) : "memory");
}

void outw(uint16_t port, uint16_t val) {
  __asm__ volatile ("outw %0, %1" : : "a"(val), "Nd"(port) : "memory");
}

void outd(uint16_t port, uint32_t val) {
  __asm__ volatile ("outl %0, %1" : : "a"(val), "Nd"(port) : "memory");
}


uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ( "inb %1, %0"
            : "=a"(ret)
            : "Nd"(port)
            : "memory");
    return ret;
}


uint16_t inw(uint16_t port) {
  uint16_t ret;
  __asm__ volatile ( "inw %1, %0"
            : "=a"(ret)
            : "Nd"(port)
            : "memory"); 
  return ret;
}

uint32_t ind(uint16_t port) {
  uint32_t ret;
  __asm__ volatile ( "inl %1, %0"
            : "=a"(ret)
            : "Nd"(port)
            : "memory"); 
  return ret;
}

void io_wait(void)
{
    outb(0x80, 0);
}

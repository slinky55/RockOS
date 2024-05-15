#ifndef _i386_idt_h
#define _i386_idt_h

#include <stdint.h>

typedef struct {
  uint16_t offset_l;
  uint16_t selector;
  uint8_t zero;
  uint8_t attribs;
  uint16_t offset_h;
} __attribute__((packed)) idt_entry_t;

typedef struct {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) idtr_t;


void init_idt();

#endif 

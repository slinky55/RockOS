#include <arch/i386/idt.h>

__attribute__((aligned(0x10)))

static idt_entry_t idt[256];
static idtr_t idtr;

extern void* isr_stub_table[];

void set_idt_desc(uint8_t _v, void* _isr, uint8_t _flags) {
  idt_entry_t* desc = &idt[_v];

  desc->offset_l = (uint32_t)_isr & 0xFFFF;      
  desc->selector = 0x08;
  desc->attribs = _flags;
  desc->offset_h = (uint32_t)_isr >> 16;
  desc->zero = 0;
}

void init_idt() {
  idtr.base = (uint32_t)&idt[0];
  idtr.limit = 2047;

  // exceptions
  for (uint8_t v = 0; v < 32; v++) {
    set_idt_desc(v, isr_stub_table[v], 0x8E); 
  }

  __asm__ volatile ("lidt %0" : : "m"(idtr));
}

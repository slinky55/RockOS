#include <arch/i386/idt.h>

__attribute__((aligned(0x10)))

static idt_entry_t idt[256];
static idtr_t idtr;

extern void* isr_stub_table[];

void default_isr_handler() {
  puts("isr handler...");
}

void set_idt_desc(uint8_t _v, void* _isr, uint8_t _flags) {
  idt_entry_t* desc = &idt[_v];

  desc->offset_l = (uint32_t)_isr & 0xFFFF;      
  desc->selector = 0x08;
  desc->attribs = _flags;
  desc->offset_h = (uint32_t)_isr >> 16;
  desc->zero = 0;
}

void init_idt() {
  puts("loading idt...");

  idtr.base = (uint32_t)&idt[0];
  idtr.limit = sizeof(idt) - 1;

  // exceptions (0 - 31)
  for (uint8_t v = 0; v < 32; v++) {
    set_idt_desc(v, isr_stub_table[v], 0x8E); 
  }

  set_idt_desc(0x20, isr_stub_table[0x20], 0x8E);
  set_idt_desc(0x21, isr_stub_table[0x21], 0x8E);

  __asm__ volatile ("lidt %0" : : "m"(idtr));

  puts("idt done...");
}

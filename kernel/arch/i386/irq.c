#include <arch/i386/irq.h>

#include <stdio.h>
#include <arch/i386/pic.h>

extern void* isr_stub_table[];
extern void set_idt_desc(uint8_t, void*, uint8_t);

uint32_t timer_ticks = 0;

irq_handler

void timer_irq_handler(irq_reg_t* regs) {
  timer_ticks++;

  if (timer_ticks % 18 == 0) {
    puts("one second...");
  }

  pic_eoi(0);
}

void keyboard_irq_handler(irq_reg_t* regs) {
  puts("keyboard event");
  pic_eoi(1);
}

void init_irq() {
  set_idt_desc(0x20, isr_stub_table[0x20], 0x8E);
  set_idt_desc(0x21, isr_stub_table[0x21], 0x8E);
}

#include <arch/i386/irq.h>

#include <stdio.h>
#include <arch/i386/pic.h>

#include <arch/i386/idt.h>

#include <arch/i386/ports.h>

extern void* irq_stub_table[];
extern void set_idt_desc(uint8_t, void*, uint8_t);

void timer_irq_handler(irq_regs_t* regs);
void keyboard_irq_handler(irq_regs_t* regs);

void (*handler_funcs[16])(irq_regs_t* regs) = {
  timer_irq_handler,
  keyboard_irq_handler,
};

void irq_handler(irq_regs_t* regs) {
  handler_funcs[regs->irq_no](regs);
}

int timer_ticks = 0;
int seconds_running = 0;
void timer_irq_handler(irq_regs_t* regs) {
  timer_ticks++;

  if (timer_ticks % 100 == 0) {
    seconds_running++;
  }

  pic_eoi(0);
}

int brk = 0;
extern char ps2_set_1[128];
void keyboard_irq_handler(irq_regs_t* regs) {
  if (brk == 1) {
    brk = 0;
    inb(0x60);
    pic_eoi(1);
    return;
  } 

  uint8_t scancode = inb(0x60);
  if (scancode < 0x81) {
    putchar(ps2_set_1[scancode]);
  }
  pic_eoi(1);
}

void init_irq() {
  set_idt_desc(0x20, irq_stub_table[0x0], 0x8E);
  set_idt_desc(0x21, irq_stub_table[0x1], 0x8E);
}

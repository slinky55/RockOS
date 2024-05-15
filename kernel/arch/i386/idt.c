#include <arch/i386/idt.h>
#include <arch/i386/pic.h>
#include <arch/i386/isr.h>
#include <stdio.h>

__attribute__((aligned(0x10)))

idt_entry_t idt[MAX_IDT_ENTRIES];
idtr_t idtr;

extern void* isr_stub_table[];

extern void load_idt();

unsigned char *exception_msgs[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(isr_regs_t* regs) {
  if (regs->int_no < 32) {
    puts("exception!!!");
    puts(exception_msgs[regs->int_no]);
    puts("halting...");
    asm("cli");
    asm("hlt");
  }
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
  idtr.limit = MAX_IDT_ENTRIES * sizeof(idt_entry_t) - 1;

  // exceptions (0 - 31)
  for (uint8_t v = 0; v < 32; v++) {
    set_idt_desc(v, isr_stub_table[v], 0x8E); 
  }

  load_idt();

  puts("idt done...");
}

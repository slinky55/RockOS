#include <stdio.h>

#include <kernel/tty.h>

#include <arch/i386/gdt.h>
#include <arch/i386/idt.h>
#include <arch/i386/irq.h>
#include <arch/i386/pic.h>
#include <arch/i386/timer.h>

void kernel_early() {
  terminal_initialize();

  init_gdt();
  init_idt();

  init_pic(0x20, 0x28);
  init_irq();

  init_pit();
}

void kernel_main() {
	puts("RockOS booting...");
}

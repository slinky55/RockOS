#include <stdio.h>

#include <kernel/tty.h>
#include <arch/i386/gdt.h>

#include <arch/i386/pic.h>

void kernel_early(void) {
  init_pic(0x20, 0x28);
}

void kernel_main(void) {
	puts("RockOS booting...");
}

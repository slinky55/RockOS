#include <stdio.h>

#include <kernel/tty.h>
#include <arch/i386/gdt.h>

#include <arch/i386/pic.h>

void kernel_main(void) {
	puts("RockOS booting...");

  init_pic(0x20, 0x28);
}

#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>

void kernel_main(void) {
	gdt_initialize();
	terminal_initialize();

	printf("Starting RockOS...");
}

# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

.section .multiboot.data, "aw"
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .bss, "aw", @nobits
.align 4096

.global k_page_directory
k_page_directory:
.skip 4096

.global k_page_table
k_page_table:
.skip 4096

.section .multiboot.text, "a"
.global _start
.type _start, @function
_start:

	movl $(k_page_table - 0xC0000000), %edi

	movl $0, %esi

	movl $1023, %ecx

1:
	cmpl $_kernel_start, %esi
	jl 2f
	cmpl $(_kernel_end - 0xC0000000), %esi
	jge 3f

	movl %esi, %edx
	orl $0x003, %edx
	movl %edx, (%edi)

2:
	addl $4096, %esi
	addl $4, %edi
	loop 1b

3:
	movl $(0x000B8000 | 0x003), k_page_table - 0xC0000000 + 1023 * 4
	movl $(k_page_table - 0xC0000000 + 0x003), k_page_directory - 0xC0000000 + 0
	movl $(k_page_table - 0xC0000000 + 0x003), k_page_directory - 0xC0000000 + 768 * 4
	
	movl $(k_page_directory - 0xC0000000), %ecx
	movl %ecx, %cr3

	# Enable paging and the write-protect bit.
	movl %cr0, %ecx
	orl $0x80010000, %ecx
	movl %ecx, %cr0

	# Jump to higher half with an absolute jump. 
	lea 4f, %ecx
	jmp *%ecx

.section .text

4:
	# At this point, paging is fully set up and enabled.

	# Unmap the identity mapping as it is now unnecessary. 
	movl $0, k_page_directory + 0

	# Reload crc3 to force a TLB flush so the changes to take effect.
	movl %cr3, %ecx
	movl %ecx, %cr3

	# Set up the stack.
	mov $stack_top, %esp

	# Enter the high-level kernel.
	call kernel_main

	# Infinite loop if the system has nothing more to do.
	cli
1:	hlt
	jmp 1b
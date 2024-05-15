.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp

	call _init

  cli

  call kernel_early

  sti

  call kernel_main

  int $0x21

  cli
1:	hlt
	jmp 1b
.size _start, . - _start


.global load_gdt
load_gdt:
  lgdt [gdt_ptr]

  push %eax   

  mov $0x10, %ax
  mov %ax, %ds
  mov %ax, %es 
  mov %ax, %fs 
  mov %ax, %gs 
  mov %ax, %ss
  
  ljmp $0x08, $flush_gdt

flush_gdt:
  pop %eax
  ret

.global load_idt 
load_idt:
  lidt [idtr]
  ret

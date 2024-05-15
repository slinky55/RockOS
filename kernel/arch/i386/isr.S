.global default_isr_handler

.macro isr_stub_err num
isr_stub_\num:
  cli
  push $\num
  jmp isr_common
.endm

.macro isr_stub_n_err num 
isr_stub_\num:
  push $0 
  push $\num
  jmp isr_common
.endm

.macro irq_stub num 
irq_\num: 
  push $0 
  push $\num 
  jmp irq_common

.section .text
isr_common:
  pusha 

  push %ds 
  push %es 
  push %fs 
  push %gs 
  
  mov $0x10, %ax 
  mov %ax, %ds 
  mov %ax, %es 
  mov %ax, %fs 
  mov %ax, %gs

  mov %esp, %eax 
  push %eax 

  call isr_handler

  pop %eax 
  pop %gs
  pop %fs 
  pop %es 
  pop %ds

  popa

  add $0x08, %esp

  iret

irq_common:
  pusha 

  push %ds 
  push %es 
  push %fs 
  push %gs 
  
  mov $0x10, %ax 
  mov %ax, %ds 
  mov %ax, %es 
  mov %ax, %fs 
  mov %ax, %gs

  mov %esp, %eax 
  push %eax 

  call irq_handler

  pop %eax 
  pop %gs
  pop %fs 
  pop %es 
  pop %ds

  popa

  add $0x08, %esp

  iret
  
isr_stub_n_err 0
isr_stub_n_err 1 
isr_stub_n_err 2 
isr_stub_n_err 3 
isr_stub_n_err 4 
isr_stub_n_err 5 
isr_stub_n_err 6 
isr_stub_n_err 7
isr_stub_err 8 
isr_stub_n_err 9 
isr_stub_err 10 
isr_stub_err 11 
isr_stub_err 12 
isr_stub_err 13 
isr_stub_err 14
isr_stub_n_err 15 
isr_stub_n_err 16
isr_stub_n_err 17 
isr_stub_n_err 18 
isr_stub_n_err 19
isr_stub_n_err 20 
isr_stub_n_err 21 
isr_stub_n_err 22 
isr_stub_n_err 23 
isr_stub_n_err 24 
isr_stub_n_err 25 
isr_stub_n_err 26 
isr_stub_n_err 27 
isr_stub_n_err 28 
isr_stub_n_err 29 
isr_stub_n_err 30 
isr_stub_n_err 31

irq_0:
  push $0x00
  push $0x00

  pusha 

  push %ds 
  push %es 
  push %fs 
  push %gs 
  
  mov $0x10, %ax 
  mov %ax, %ds 
  mov %ax, %es 
  mov %ax, %fs 
  mov %ax, %gs

  mov %esp, %eax 
  push %eax 

  call timer_irq_handler

  pop %eax 
  pop %gs
  pop %fs 
  pop %es 
  pop %ds

  popa

  add $0x08, %esp

  iret

irq_1:
  push $0x00 
  push $0x01

  pusha 

  push %ds 
  push %es 
  push %fs 
  push %gs 
  
  mov $0x10, %ax 
  mov %ax, %ds 
  mov %ax, %es 
  mov %ax, %fs 
  mov %ax, %gs

  mov %esp, %eax 
  push %eax 

  call keyboard_irq_handler

  pop %eax 
  pop %gs
  pop %fs 
  pop %es 
  pop %ds

  popa

  add $0x08, %esp

  iret

.section .data
.global isr_stub_table
isr_stub_table:
.long isr_stub_0
.long isr_stub_1
.long isr_stub_2
.long isr_stub_3
.long isr_stub_4
.long isr_stub_5
.long isr_stub_6
.long isr_stub_7
.long isr_stub_8
.long isr_stub_9
.long isr_stub_10
.long isr_stub_11
.long isr_stub_12
.long isr_stub_13
.long isr_stub_14
.long isr_stub_15
.long isr_stub_16
.long isr_stub_17
.long isr_stub_18
.long isr_stub_19
.long isr_stub_20
.long isr_stub_21
.long isr_stub_22
.long isr_stub_23
.long isr_stub_24
.long isr_stub_25
.long isr_stub_26
.long isr_stub_27
.long isr_stub_28
.long isr_stub_29
.long isr_stub_30
.long isr_stub_31

.global irq_stub_table
irq_stub_table:
.long irq_0
.long irq_1

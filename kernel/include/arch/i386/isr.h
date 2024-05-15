#ifndef _arch_i386_isr_h
#define _arch_i386_isr_h

typedef struct{
  unsigned int gs, fs, es, ds;
  unsigned int edi, esi, edp, esp, ebx, edx, ecx, eax;
  unsigned int int_no, err_code;
  unsigned int eip
} isr_regs_t;

#endif

#ifndef _arch_i386_isr_h
#define _arch_i386_isr_h

#include <stdint.h>

typedef struct{
  uint32_t gs, fs, es, ds;
  uint32_t edi, esi, edp, esp, ebx, edx, ecx, eax;
  uint32_t int_no, err_code;
  uint32_t eip, cs, eflags, userresp, ss;
} isr_regs_t;

#endif

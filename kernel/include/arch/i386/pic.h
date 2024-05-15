#ifndef _arch_i386_pic_h
#define _arch_i386_pic_h

#define PIC_MASTER 0x20
#define PIC_SLAVE  0xA0

#define PIC_M_CMD  PIC_MASTER
#define PIC_M_DATA 0x21

#define PIC_S_CMD  PIC_SLAVE
#define PIC_S_DATA 0xA1

#define PIC_EOI 0x20

#define ICW1_ICW4	0x01		/* Indicates that ICW4 will be present */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

#include <stdint.h>

void init_pic(uint8_t m_off, uint8_t s_off);

void pic_eoi(uint8_t irq);

void enable_irq(uint8_t irq);
void disable_irq(uint8_t irq);

#endif

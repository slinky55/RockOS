#include <arch/i386/pic.h>
#include <arch/i386/ports.h>

#include <stdio.h>

void init_pic(uint8_t m_off, uint8_t s_off) {
  puts("initializing pic...");

  outb(PIC_M_CMD, ICW1_INIT | ICW1_ICW4);
  io_wait();
  outb(PIC_S_CMD, ICW1_INIT | ICW1_ICW4);
  io_wait();
  outb(PIC_M_DATA, m_off);
  io_wait();
  outb(PIC_S_DATA, s_off);
  io_wait();
  outb(PIC_M_DATA, 4);
  io_wait();
  outb(PIC_S_DATA, 2);
  io_wait();

  outb(PIC_M_DATA, ICW4_8086);
  io_wait();
  outb(PIC_S_DATA, ICW4_8086);
  io_wait();

  outb(PIC_M_DATA, 0x00);
  outb(PIC_S_DATA, 0x00);  

  puts("pic done");
}

void pic_eoi(uint8_t irq)
{
	if(irq >= 8)
		outb(PIC_SLAVE, PIC_EOI);
 
	outb(PIC_MASTER, PIC_EOI);
}

void enable_irq(uint8_t irq) {
  uint16_t port;
  uint8_t value;

  if (irq < 8) {
    port = PIC_M_DATA;
  } else {
    port = PIC_S_DATA;
    irq -= 8;
  }

  value = inb(port) & ~(1 << irq);
  outb(port, value);
}

void disable_irq(uint8_t irq) {
  uint16_t port;
  uint8_t value;
 
  if(irq < 8) {
    port = PIC_M_DATA;
  } else {
    port = PIC_S_DATA;
    irq -= 8;
  }

  value = inb(port) | (1 << irq);
  outb(port, value);   
}

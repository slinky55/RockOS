#include <arch/i386/pic.h>
#include <arch/i386/ports.h>

void init_pic(uint8_t m_off, uint8_t s_off) {
  uint8_t m_mask;
  uint8_t s_mask;

  m_mask = inb(PIC_MASTER);
  s_mask = inb(PIC_SLAVE);
  
  outb(PIC_MASTER, ICW1_INIT | ICW1_ICW4);
  io_wait();
  outb(PIC_SLAVE, ICW1_INIT | ICW1_ICW4);
  io_wait();
  outb(PIC_MASTER, m_off);
  io_wait();
  outb(PIC_SLAVE, s_off);
  io_wait();
  outb(PIC_MASTER, 4);
  io_wait();
  outb(PIC_SLAVE, 2);
  io_wait();

  outb(PIC_MASTER, ICW4_8086);
  io_wait();
  outb(PIC_SLAVE, ICW4_8086);
  io_wait();

  outb(PIC_MASTER, m_mask);
  outb(PIC_SLAVE, s_mask);  
}


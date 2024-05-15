#include <arch/i386/timer.h> 
#include <arch/i386/ports.h>

#include <stdio.h>

void timer_phase(int hz)
{
  int divisor = 1193180 / hz;       /* Calculate our divisor */
  outb(0x43, 0x36);             /* Set our command byte 0x36 */
  outb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
  outb(0x40, divisor >> 8);     /* Set high byte of divisor */
}

void init_pit() {
  puts("initializing pit...");
  timer_phase(100);
  puts("pit done");
}


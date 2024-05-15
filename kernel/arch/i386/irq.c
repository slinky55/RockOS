#include <stdio.h>
#include <arch/i386/pic.h>

uint32_t timer_ticks = 0;

void timer_irq_handler() {
  timer_ticks++;

  if (timer_ticks % 18 == 0) {
    puts("one second...");
  }

  pic_eoi(0);
}

void keyboard_irq_handler() {
  puts("keyboard event");
  pic_eoi(1);
}

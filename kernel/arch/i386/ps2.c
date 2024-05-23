#include <kernel/ps2.h>

#include <arch/i386/ports.h>

#include <stdint.h>
#include <stdio.h>

void poll_input_ready() {
  uint8_t status = inb(PS2_STATUS);
  while (1) {
    int buffStatus = (status & 0b00000010) == 0;
    if (buffStatus) {
      break;
    }
    status = inb(PS2_STATUS);
  }
}

void poll_output_ready() {
  uint8_t status = inb(PS2_STATUS);
  while (1) { // poll until output buffer is full 
    int buffStatus = (status & 0b00000001) == 1;
    if (buffStatus) {
      break;
    }
    status = inb(PS2_STATUS);
  }
}

void flush_output() {
  while(1) { // poll and read until buffer is empty
    uint8_t status = inb(PS2_STATUS);
    int buffStatus = (status & 0b00000001) == 1;
    if (!buffStatus) {
      break;
    }
    inb(PS2_DATA);
  }
}

void test_ps2_controller() {
  poll_input_ready();
  outb(PS2_COMMAND, 0xAA);
  poll_output_ready();
  uint8_t resp = inb(PS2_DATA);
  if (resp == 0x55) {
    puts("ps/2 controller pass");
  } else {
    puts("ps/2 controller fail");
  }
}

void test_ps2_port_1() {
  poll_input_ready();
  outb(PS2_COMMAND, 0xAB);
  poll_output_ready();
  uint8_t resp = inb(PS2_DATA);
  if (resp == 0x00) {
    puts("ps/2 port 1 pass");
  }
}

void test_ps2_port_2() {
  poll_input_ready();
  outb(PS2_COMMAND, 0xA9);
  poll_output_ready();
  uint8_t resp = inb(PS2_DATA);
  if (resp == 0x00) {
    puts("ps/2 port 2 pass");
  }
}


void init_ps2_controller() {
  puts("ps2 init");

  // disable both ps2 ports
  poll_input_ready();
  outb(PS2_COMMAND, 0xA7);
  poll_input_ready();
  outb(PS2_COMMAND, 0xAD);

  flush_output();

  poll_input_ready();
  outb(PS2_COMMAND, 0x20);
  poll_output_ready();
  uint8_t cfg = inb(PS2_DATA);
  int isDual = (cfg & 0b00010000) == 0b00010000;

  // clear bits 0, 1
  cfg = 0b00011100;

  if (isDual) {
    puts("found dual ps/2");
  }

  poll_input_ready();
  outb(PS2_COMMAND, 0x60);
  poll_input_ready();
  outb(PS2_DATA, cfg);

  test_ps2_controller();
  test_ps2_port_1();
  test_ps2_port_2();

  cfg |= 0b00000011;
  poll_input_ready();
  outb(PS2_COMMAND, 0x60);
  poll_input_ready();
  outb(PS2_DATA, cfg);

  poll_input_ready();
  outb(PS2_COMMAND, 0xAE);
  poll_input_ready();
  outb(PS2_COMMAND, 0xA8);

  puts("ps2 done");
}

void init_ps2_keyboard() {
}

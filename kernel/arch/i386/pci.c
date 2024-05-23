#include <kernel/pci.h>

#include <arch/i386/ports.h>

#include <stdio.h>
#include <stdint.h>

uint32_t pci_in(uint32_t bus, uint32_t dev, uint32_t func, uint32_t offset) {
  outd(CFG_ADDRESS, (0x80000000 | (bus << 16) | (dev << 11) | (func << 8) | (offset)));
  return ind(CFG_DATA);
}

void pci_out(uint32_t bus, uint32_t dev, uint32_t func, uint32_t offset, uint32_t val) {
  outd(CFG_ADDRESS, (0x80000000 | (bus << 16) | (dev << 11) | (func << 8) | (offset)));
  outd(CFG_DATA, val);
}

uint32_t num_uhci = 0;
uint32_t num_ohci = 0;

void scan_device(uint32_t bus, uint32_t dev, uint32_t func);
void scan_pci() {
  puts("scanning PCI");  

  for (int bus = 0; bus < 256; bus++) {
    for (int dev = 0; dev < 32; dev++) {
      scan_device(bus, dev, 0);

      int multifunc = (pci_in(bus, dev, 0, 0x0C) & MULTIFUNC_FLAG) == MULTIFUNC_FLAG;
      if (multifunc) {
        for (int func = 1; func < 8; func++) {
          scan_device(bus, dev, func);
        }
      }
    }
  }

  puts("pci done");
  if (num_uhci > 0) {
    puts("found uhci");
  }

  if (num_ohci > 0) {
    puts("found ohci");
  }
}


void scan_device(uint32_t bus, uint32_t dev, uint32_t func) {
  uint32_t full_dev_did, vendor_id, dev_id, type, class, subclass, progif, mmio_base;
  uint16_t io_base;

  full_dev_did = pci_in(bus, dev, func, 0);  
  vendor_id = full_dev_did & 0xFFFF;
  dev_id = full_dev_did >> 16;

  if (full_dev_did == 0xFFFFFFFF) {
    return;
  }

  type = pci_in(bus, dev, func, 0x08) >> 8;
  class = type >> 16;
  subclass = (type >> 8) & 0xFF;
  progif = type & 0xFF;

  switch (type) {
  case OHCI:
    num_ohci++;
  case UHCI:
    pci_out(bus, dev, func, 0xC0, 0x8F00);
    num_uhci++;
  }
}

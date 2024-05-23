#ifndef _k_pci_h
#define _k_pci_h

#define CFG_ADDRESS 0xCF8
#define CFG_DATA 0xCFC

#define MULTIFUNC_FLAG 0x00800000

#define OHCI 0x0C0310
#define UHCI 0x0C0300
#define EHCI 0x0C0320
#define XHCI 0x0C0330

void scan_pci();

#endif

#ifndef _k_ps2_h
#define _k_ps2_h

#define PS2_DATA 0x60 
#define PS2_STATUS 0x64 
#define PS2_COMMAND 0x64

void init_ps2_controller();
void init_ps2_keyboard();

#endif

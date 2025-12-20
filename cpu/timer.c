#include "timer.h"
#include "../drivers/screen.h"
#include "../libc/string.h"
#include "isr.h"

unsigned int tick = 0;

static void timer_callback(registers_t r){
    tick++;
}

void init_timer(unsigned int freq){
    register_interrupt_handler(32,timer_callback);

    unsigned int divisor = 1193180 / freq;
    unsigned short low  = (unsigned short)(divisor & 0xFF);
    unsigned short high = (unsigned short)( (divisor >> 8) & 0xFF);
    
    /* Send the command */
    port_byte_out(0x43, 0x36); 
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}
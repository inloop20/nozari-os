#include "./idt.h"

idt_entry_t idt[256];
idt_ptr_t idt_ptr;

void set_idt_entries(int num,unsigned int handler){
    idt[num].low_16 = (unsigned short)(handler & 0xFFFF);
    idt[num].high_16 = (unsigned short) ((handler >> 16) & 0xFFFF);     
    idt[num].selector = 0x08;
    idt[num].always_zero = 0;
    idt[num].flag = 0x8E; 
}

void set_idt_ptr(){
    idt_ptr.base = (unsigned int)&idt; 
    idt_ptr.limit = sizeof(idt_entry_t)*256-1;

    __asm__ __volatile__("lidtl (%0)"  : : "r" (&idt_ptr));
}
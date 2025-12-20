#ifndef IDT_H
#define IDT_H

typedef struct {
    unsigned short limit; //0x2000
    unsigned int base; //0x2017
} __attribute__((packed)) idt_ptr_t;

typedef struct {
    unsigned short low_16;
    unsigned short selector; 
    unsigned char always_zero; 
    unsigned char flag;
    unsigned short high_16;
} __attribute__((packed)) idt_entry_t;



void set_idt_entries(int num, unsigned int handler);
void set_idt_ptr();

#endif

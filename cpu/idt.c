typedef struct {
    unsigned short limit;
    unsigned int base;
}__attribute__((packed)) idt_ptr_t

typedef struct {
    unsigned short low_16; //lower 16 bits of handler address
    unsigned short selector; //kernel code segment selector (from gdt)
    unsigned char always_zero; //always zero
    unsigned char flag; /* Bit 7	P (Present)	
    Bits 6-5	DPL (Descriptor Privilege Level) 
    Bit 4	Must be 0.	
    Bits 3-0	Gate Type */ 
    unsigned short high_16; //higher 16 bits of handler address
}__attribute__((packed)) idt_entry_t

    /* 256 entries  
    0-31 cpu reserved
    32-47 hardware interrupts
    48-255 software interrupts
    */
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
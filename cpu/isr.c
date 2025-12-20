#include "isr.h"
#include "idt.h"
#include "../libc/string.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "timer.h"
#include "port.h"

isr_t interrupt_handlers[256];

void register_interrupt_handler(unsigned short num, isr_t handler) {
    interrupt_handlers[num] = handler;
}

void install_isr(){
        set_idt_entries(0,(unsigned int)isr0);
        set_idt_entries(1,(unsigned int)isr1);
        set_idt_entries(2,(unsigned int)isr2);
        set_idt_entries(3,(unsigned int)isr3);
        set_idt_entries(4,(unsigned int)isr4);
        set_idt_entries(5,(unsigned int)isr5);
        set_idt_entries(6,(unsigned int)isr6);
        set_idt_entries(7,(unsigned int)isr7);
        set_idt_entries(8,(unsigned int)isr8);
        set_idt_entries(9,(unsigned int)isr9);
        set_idt_entries(10,(unsigned int)isr10);
        set_idt_entries(11,(unsigned int)isr11);
        set_idt_entries(12,(unsigned int)isr12);
        set_idt_entries(13,(unsigned int)isr13);
        set_idt_entries(14,(unsigned int)isr14);
        set_idt_entries(15,(unsigned int)isr15);
        set_idt_entries(16,(unsigned int)isr16);
        set_idt_entries(17,(unsigned int)isr17);
        set_idt_entries(18,(unsigned int)isr18);
        set_idt_entries(19,(unsigned int)isr19);
        set_idt_entries(20,(unsigned int)isr20);
        set_idt_entries(21,(unsigned int)isr21);
        set_idt_entries(22,(unsigned int)isr22);
        set_idt_entries(23,(unsigned int)isr23);
        set_idt_entries(24,(unsigned int)isr24);
        set_idt_entries(25,(unsigned int)isr25);
        set_idt_entries(26,(unsigned int)isr26);
        set_idt_entries(27,(unsigned int)isr27);
        set_idt_entries(28,(unsigned int)isr28);
        set_idt_entries(29,(unsigned int)isr29);
        set_idt_entries(30,(unsigned int)isr30);
        set_idt_entries(31,(unsigned int)isr31);

        //intializing
        port_byte_out(0x20,0x11);
        port_byte_out(0xA0,0x11);

        //remap
        port_byte_out(0x21,0x20);
        port_byte_out(0xA1,0x28);

        //master/slave wiring
        port_byte_out(0x21,0x04);
        port_byte_out(0xA1,0x02);

        // Set PIC mode (ICW4)
        port_byte_out(0x21,0x01);
        port_byte_out(0xA1,0x01);

        //Unmask all IRQ lines
        port_byte_out(0x21,0x0);
        port_byte_out(0xA1,0x0);
        
        set_idt_entries(32,(unsigned int)irq0);
        set_idt_entries(33,(unsigned int)irq1);
        set_idt_entries(34,(unsigned int)irq2);
        set_idt_entries(35,(unsigned int)irq3);
        set_idt_entries(36,(unsigned int)irq4);
        set_idt_entries(37,(unsigned int)irq5);
        set_idt_entries(38,(unsigned int)irq6);
        set_idt_entries(39,(unsigned int)irq7);
        set_idt_entries(40,(unsigned int)irq8);
        set_idt_entries(41,(unsigned int)irq9);
        set_idt_entries(42,(unsigned int)irq10);
        set_idt_entries(43,(unsigned int)irq11);
        set_idt_entries(44,(unsigned int)irq12);
        set_idt_entries(45,(unsigned int)irq13);
        set_idt_entries(46,(unsigned int)irq14);
        set_idt_entries(47,(unsigned int)irq15);


        set_idt_ptr();
}

char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(registers_t r){
    kprint("recieved interrupt: ");
    char str[4]; 
    itoa(r.int_no, str);
    kprint(str);
    kprint("\n");
    kprint(exception_messages[r.int_no]);
    kprint("\n");
}

void irq_handler(registers_t r){
    if(r.int_no >=40)
        port_byte_out(0xA0,0x20);
    port_byte_out(0x20,0x20);

    if(interrupt_handlers[r.int_no]!=0){
        isr_t handler =  interrupt_handlers[r.int_no]; 
        handler(r);
    }    
}

void install_irq(){
     asm volatile("sti");
     init_timer(50);
     init_keyboard();
}
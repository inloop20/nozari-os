#include "idt.c";
#include "./kernel/kernel.c";

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

typedef struct {
     unsigned int ds, /* Data segment selector */
    edi, esi, ebp, esp, ebx, edx, ecx, eax, /* Pushed by pusha. */
    int_no, err_code, /* Interrupt number and error code (if applicable) */
    eip, cs, eflags, useresp, ss; /* Pushed by the processor automatically */
} registers_t;


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
    char str[3];
      int i, sign,n=r.int_no;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    kprint(str);
    kprint("\n");
    kprint(exception_messages[r.int_no]);
    kprint("\n");

}
#include "keyboard.h"
#include "screen.h"
#include "../cpu/isr.h"
#include "../cpu/port.h"
#include "../libc/string.h"

char input_buffer[256];

const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r', 't', 'y', 
        'u', 'i', 'o', 'p', '[', ']', '?', '?', 'a', 's', 'd', 'f', 'g', 
        'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v', 
        'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' '};

static void keyboard_handler(registers_t r){
    unsigned short scan_code = port_byte_in(0x60);
    if(scan_code >57) return;
    if(scan_code == 0x0E){
        pop(input_buffer);
        kprint_backspace();
    }else if(scan_code == 0x1C){
        kprint("\n");
    }else{
        char letter = sc_ascii[(int)scan_code];
        char str[2] = {letter, '\0'};
        kprint(str); 
    }
}

void init_keyboard(){
    register_interrupt_handler(33, keyboard_handler);
}

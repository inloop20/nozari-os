#include "../cpu/isr.h"
#include "../cpu/timer.h"
 #include "../drivers/keyboard.h"
 #include "../drivers/screen.h"
void main() {
   install_isr();
   install_irq();
   clear_screen();
 
    
}
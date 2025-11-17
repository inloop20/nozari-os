#include "../drivers/screen.h"
void main() {
  clear_screen(); 
   kprint_at("Hello world", 0, 1);
    kprint_at("This text spans multiple lines", 2, 75);
    kprint_at("There is a line\nbreak", 4, 0);
    kprint("There is a line\nbreak");
    kprint_at("What happens when we run out of space?", 24, 45);
   
     
}
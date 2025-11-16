/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
void dummy_test_entrypoint() {
}

void main() {
      char* video_memory = (char*) (0xb8000 + 2 * 80 * 14); 

    char* msg = "Hello World";

    for (int i = 0; msg[i] != 0; i++) {
        video_memory[i*2] = msg[i];     
        video_memory[i*2 + 1] = 0x0D;   
    }
}
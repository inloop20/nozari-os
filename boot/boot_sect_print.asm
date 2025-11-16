print:
    pusha
    print_loop:
        mov al,[bx]
        cmp al,0
        je finish_print
        mov ah,0x0e
        int 0x10
        inc bx
        jmp print_loop
    finish_print:
        popa
        ret
print_nl:
    pusha
    
    mov ah, 0x0e
    mov al, 0x0a
    int 0x10
    mov al, 0x0d 
    int 0x10
    
    popa
    ret
        
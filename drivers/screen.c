#include "screen.h"
#include "port.h"

int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);
void set_cursor_offset(int offset);
int get_cursor_offset();

int printc(char c, int row, int col, char attr){
    unsigned char *vga = (unsigned char *)(VIDEO_ADDRESS);
    if (!attr)
        attr = WHITE_ON_BLACK;
     if (row >= MAX_ROWS || col >= MAX_COLS){
         vga[2 * (MAX_COLS) * (MAX_ROWS)-2] = 'E';
         vga[2 * (MAX_COLS) * (MAX_ROWS)-1] = RED_ON_WHITE;
         return get_offset(col, row);
     }
    int offset;
    if (col >= 0 && row >= 0)
        offset = get_offset(col, row);
    else
        offset = get_cursor_offset();
    if (c == '\n'){
        row = get_offset_row(offset);
        offset = get_offset(0, row + 1);
    }
    else{
        vga[offset] = c;
        vga[offset + 1] = attr;
        offset += 2;
    }
    if(get_offset_row(offset)>=25){
       scroll();
        offset -=2*MAX_COLS ;
    }
    set_cursor_offset(offset);
    return offset;
}

void scroll(){
    char* vga = (char*) VIDEO_ADDRESS;
     for(int i=0;i<((MAX_ROWS-1)*MAX_COLS)*2;i+=2){
           vga[i] = vga[i+MAX_COLS*2];
           vga[i+1] = vga[i+1+MAX_COLS*2];
        }
       
        for(int i=(MAX_ROWS-1)*MAX_COLS;i<MAX_ROWS*MAX_COLS;i++) vga[i*2] = ' ';
}

void kprint_at(char *message, int row, int col)
{
    int offset;
    if (row >= 0 && col >= 0)
    {
        offset = get_offset(col, row);
    }
    else
    {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
    int i = 0;
    while (message[i])
    {
        offset = printc(message[i++], row, col, WHITE_ON_BLACK);
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}
void kprint(char *message)
{
    kprint_at(message, -1, -1);
}

void set_cursor_offset(int offset)
{
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void clear_screen()
{
    int screen_size = MAX_ROWS * MAX_COLS;
    char *screen = VIDEO_ADDRESS;
    for (int i = 0; i < screen_size; i++)
    {
        screen[i * 2] = ' ';
        screen[i * 2 + 1] = WHITE_ON_BLACK;
    }
    set_cursor_offset(get_offset(0, 0));
}

int get_cursor_offset()
{
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2;
    ;
}

int get_offset(int col, int row)
{
    return 2 * (row * 80 + col);
}
int get_offset_row(int offset)
{
    return offset / (2 * (MAX_COLS));
}

int get_offset_col(int offset)
{
    return (offset - (get_offset_row(offset) * 2 * (MAX_COLS))) / 2;
}
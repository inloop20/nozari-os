#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4


#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5
void init_cursor();
void clear_screen();
void kprint_at(char *message, int row, int col);
void kprint(char *message);
int printc(char c,int row,int col,char attr);
void kprint_backspace();
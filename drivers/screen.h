//vga
#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

void clear_screen();
void print(char* message);
void print_string_at_coordinate(char* message, int x, int y);
void print_char(char c, int x, int y,char attr);

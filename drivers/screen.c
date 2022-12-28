#include "screen.h"
#include "ports.h"
#include "../kernel/util.h"

///private interface, public is located at #include sections
void print_char(char character,int x,int y, char attribute);
int get_cursor_offset();
void set_cursor(int offset);
int get_screen_offset(int x,int y);
int handle_scrolling(int cursor_offset);


//print a character on the screen at (row, col)
// 				  or at cursor position
void print_char(char character,int x,int y,char attribute){
	if (!attribute){
		attribute=WHITE_ON_BLACK;
	}

	//get offset
	int offset;
	if (x>=0 && y>=0){
		offset=get_screen_offset(x,y);
	}else{
		offset=get_cursor_offset();
	}

	// print character
	unsigned char* vga=(char*) VIDEO_ADDRESS;
	if (character=='\n'){
		int tmp=offset/(2*MAX_COLS);// 2*80
		offset=get_screen_offset(79, tmp);
	}else{
		vga[offset]=character;
		vga[offset+1]=attribute;
	}

	///update stuff
	offset+=2;
	offset=handle_scrolling(offset);
	set_cursor(offset);

}


int get_cursor_offset(){
	out8(REG_SCREEN_CTRL,14);
	int offset=in8(REG_SCREEN_DATA)<<8;
	out8(REG_SCREEN_CTRL,15);
	offset+=in8(REG_SCREEN_DATA);
	return offset*2;
}


void set_cursor(int offset){
	offset/=2;
	out8(REG_SCREEN_CTRL,14);
	out8(REG_SCREEN_DATA,(unsigned char)(offset>>8));
	out8(REG_SCREEN_CTRL,15);
	out8(REG_SCREEN_DATA,(unsigned char)(offset & 0xff));
}

int get_screen_offset(int x,int y){
	return 2*(y*80+x);
}


void clear_screen(){
	int screen_size=MAX_COLS*MAX_ROWS;
	char* vga;
	vga=(char*)0xb8000;  //char* is a conversion
	for (int i=0;i<screen_size;i++){
		vga[2*i]=' ';
		vga[2*i+1]=WHITE_ON_BLACK;
	}
	set_cursor(0);
}


//input current cursor offset, return the new cursor offset
int handle_scrolling(int cursor_offset){
	if (cursor_offset<=(MAX_COLS*MAX_ROWS*2)){
		return cursor_offset;
	}
	for (int i=1;i<MAX_ROWS;i++){
		memory_copy(get_screen_offset(i,0) +VIDEO_ADDRESS,
			    get_screen_offset(i-1,0)+VIDEO_ADDRESS,
			    MAX_COLS*2);
	}

	//the last line is empty
	char *last_line=(char*)((MAX_ROWS-1)*MAX_COLS*2+VIDEO_ADDRESS);
	for (int i=0;i<MAX_COLS;i++){
		last_line[2*i]=0;
		last_line[2*i+1]=0;
	}
	return cursor_offset-2*MAX_COLS;
}

//print a string at a specific location of the screen
void print_string_at_coordinate(char* message, int x, int y){
 	//set cursor position to print
	if (x>=0 && y>=0){
		set_cursor(get_screen_offset(x,y));
	}

	//print
	int i=0;
	while (message[i]!=0){
		print_char(message[i],x,y,WHITE_ON_BLACK);
		i++;
	}

}


//print a string
void print(char* message){
	print_string_at_coordinate(message,-1,-1);
}

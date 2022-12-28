#include  "../drivers/screen.h"

/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
void dummy_test_entrypoint() {
}

void main() {
	char* video_memory; //= (char*) 0xb8000;
	video_memory=(char*)0xb8000;
	*video_memory = 'A';
	//*(video_memory+1) = 'B';
	
	char* tmp=(char*)0x9000;
	*tmp='h';

	tmp=(char*)0x9001;
	*tmp= 'e';

	tmp=(char*)0x9002;
	*tmp= 0;

	//*(video_memory+3) = 'D';
	//*(video_memory+4) = ';


	//*(video_memory+10)=0;
	//	*video_memory=(char*)0x1000;
	tmp=(char*) 0x9000;
	//print_char("G",10,10,WHITE_ON_BLACK);

}



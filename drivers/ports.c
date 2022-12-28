// read from port
unsigned char in8(unsigned short port){
unsigned char result;
__asm__("in %%dx, %%al":"=a"(result):"d"(port));
return result;
}

// write to port
void out8(unsigned port, unsigned char byte){
__asm__("out %%al, %%dx"::"a"(byte),"d"(port));
}


//read word from port
unsigned short in16(unsigned short port){
unsigned short result;
__asm__("in %%dx,%%ax":"=a"(result):"d"(port));
return result;
}

//write word to port
void out16(unsigned short port, unsigned short data){
__asm__("out %%ax,%%dx"::"a"(data),"d"(port));
}




























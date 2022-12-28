void memory_copy(char* source, char* destination, int bytes){
	for (int i=0;i<bytes;i++){
		*(destination+i)=*(source+i);
	}
}

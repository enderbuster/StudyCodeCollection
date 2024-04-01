#include<stdio.h>
//through this program,see the use of stderr and stdin
void main(){
	//stdin
	printf("use printf to print in stdout\n");
	//stdin
	fprintf(stdout,"use fprintf to print in stdout\n");
	//std
	fprintf(stderr,"use fprintf to print in stderr\n");
}


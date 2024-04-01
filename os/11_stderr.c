#include<stdio.h>
//through this program,see the use of stderr and stdin
void main(){
	//stdout
	printf("use printf to print in stdout\n");
	//stdout
	fprintf(stdout,"use fprintf to print in stdout\n");
	//stderr
	fprintf(stderr,"use fprintf to print in stderr\n");
}


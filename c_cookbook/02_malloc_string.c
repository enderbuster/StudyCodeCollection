#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main(){
	char s1[10]="hello";
	printf("sizeof(s1)=%d\n",(int)sizeof(s1));
	//the outpuy:sizeof(s1)=10
	printf("strlen(s1)=%d\n",(int)strlen(s1));
	//the output:strlen(s1)=5
		
	char *s2="hello!\n";
	char* pointer=malloc(sizeof(s1));
	memcpy(pointer,s1,sizeof(pointer));
	printf("s1:use sizeof to malloc-%s\n",pointer);

	
	pointer=malloc(strlen(s1)+1);
	memcpy(pointer,s1,sizeof(pointer));
	printf("s1:use strlen to malloc-%s\n",pointer);
	
	pointer=malloc(strlen(s2)+1);
	memcpy(pointer,s2,sizeof(pointer));
	printf("s2:use strlen to malloc-%s\n",pointer);	

	//the output:
	//sizeof(s1)=10
	//strlen(s1)=5
	//s1:use sizeof to malloc-hello
	//s1:use strlen to malloc-hello
	//s2:use strlen to malloc-hello!
}

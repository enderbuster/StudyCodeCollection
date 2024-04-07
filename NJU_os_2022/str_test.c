#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char * get_ptr(){
	char * dest;
	char s4[100]="hi!\n";
	dest=(char*)malloc(strlen(s4)+1);
	strcpy(dest,s4);
	return dest;
}
void main(){
	char * s1;
	char s2[10]="hihihi";
	char * s3="hello,world!";
	s1=get_ptr();
	printf("%s\n",s1);
}

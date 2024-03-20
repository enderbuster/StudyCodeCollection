#include<stdio.h>
#include<stdlib.h>

int c;

int* add(int x,int y){
	c=x+y;
	return &c;
}

int sub(int x,int y){
	c=x-y;
	return &c;
}
//指针函数 指针
int* (*f)(int x,int y);

int main(int argc,char *argv[])
{
	f=add;
	printf("1+2=%p\n",(*f)(1,2));

	f=&sub;
	printf("1-2=%p\n",(*f)(1,2));

	return 1;
}

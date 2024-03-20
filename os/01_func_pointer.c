#include<stdio.h>
#include<stdlib.h>

int add(int x,int y){
	return x+y;
}

int sub(int x,int y){
	return x-y;
}
//函数指针 function pointer
int (*f)(int x,int y);

int main(int argc,char *argv[])
{
	f=add;
	printf("1+2=%d\n",(*f)(1,2));

	f=&sub;
	printf("1-2=%d\n",(*f)(1,2));

	return 1;
}

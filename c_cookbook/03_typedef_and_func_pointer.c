#include<stdio.h>

int add(int a,int b){
	return a+b;
}
int sub(int a,int b){
	return a-b;
}
//定义函数指针
int (*f)(int,int b);
int caculate(int a,int b,int(*f)(int,int)){
	return (*f)(a,b);
}
//用typedef来定义指针函数
typedef int (*operation)(int,int);
//same as caculate
int get_answer(int a,int b,operation op){
	return op(a,b);
}
void main(){
	int a=5,b=2;
	int res=caculate(a,b,add);
	printf("a+b=%d\n",res);

	res=get_answer(a,b,sub);
	printf("a-b=%d\n",res);
}

#include<stdio.h>

void main(){
	//a and b are both type of int
	int a=3;
	int b=4;
	float res=a/b;
	printf("a/b=%f\n",res);
	//the result is 0.000000
	//to get a result of float by using +0.0
	float correct_res=a/(b+0.0);
	printf("a/b=%f\n",correct_res);
	//now the result is 0.750000
	
}

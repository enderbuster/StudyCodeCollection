#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[]){
	printf("hello(pid:%d)\n",(int) getpid());
	int rc=fork();
	if(rc<0){
		//fork failed
		fprintf(stderr,"fork failed\n");
		exit(1);
	}
	if(rc==0){
		//child process
		printf("child(pid:%d)\n",(int) getpid());
	}
	else{
		printf("parent of %d(pid:%d)\n",rc,(int) getpid());
	}

	return 0;
}


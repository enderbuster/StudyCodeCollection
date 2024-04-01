#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>

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
		//wait()will simply wait for the child process to finish
		//and the retuen code is the pid of the child
		//wait will make this programe deterministic,which means child always runs first
		int wait_rc=wait(NULL);
		printf("parent of %d(wait_rc:%d)(pid:%d)\n",rc,wait_rc,(int) getpid());
	}

	return 0;
}


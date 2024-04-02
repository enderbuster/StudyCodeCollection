#include<unistd.h>
#include<string.h>
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
		char *myargs[4];
		myargs[0]=strdup("wc");
		myargs[1]=strdup("13_execvp_wc.c");
		myargs[2]=strdup("-l");
		//NULL indicates the end of command
		myargs[3]=NULL;
		execvp(myargs[0],myargs);
		//the intresting thing is the code after exec wont run,because exec() converts the child process into a different process
		printf("this wont run,bro\n");
	}
	else{
		int wait_rc=wait(NULL);
		printf("parent of %d(wait_rc:%d)(pid:%d)\n",rc,wait_rc,(int) getpid());
	}

	return 0;
}


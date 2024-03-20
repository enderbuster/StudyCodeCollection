#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

volatile int counter=0;
int loops;

void *worker(void *arg){
	int i;
	for(i=0;i<loops;i++){
		counter++;
	}
	return NULL;
}

int main(int argc,char *argv[]){
	if(argc!=2){
		printf("should have an input!\n");
		exit(1);
	}
	loops=atoi(argv[1]);
	pthread_t t1,t2;
	printf("初始值:%d\n",counter);
	pthread_create(&t1,NULL,worker,NULL);
	pthread_create(&t2,NULL,worker,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	printf("最终值:%d\n",counter);
	return 0;
}

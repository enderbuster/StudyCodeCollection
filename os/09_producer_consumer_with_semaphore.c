#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
//this program wont stop,use ctrl+c to stop
#define MAX 3

int buffer[MAX];
int fill=0;
int use=0;
//this count has no use but show that whether the program is running as expected
int count=0;

void put(int value){
	buffer[fill]=value;
	fill=(fill+1)%MAX;
	count++;
	printf("has produced,count=%d\n",count);
}

int get(){
	int tmp=buffer[use];
	use=(use+1)%MAX;
	count--;
	printf("has consumed,count=%d\n",count);
	return tmp;
}

sem_t full,empty,mutex;

void *producer(void *arg){
	while(1){
		sem_wait(&empty);
		sem_wait(&mutex);
		put(1);
		sem_post(&mutex);
		sem_post(&full);
	}
}
void *consumer(void *arg){
	while(1){
		sem_wait(&full);
		sem_wait(&mutex);
		get();
		sem_post(&mutex);
		sem_post(&empty);
	}
}

void main(){
	sem_init(&full,0,0);
	sem_init(&empty,0,MAX);
	sem_init(&mutex,0,1);
	pthread_t p1,p2,c1,c2;
	pthread_create(&p1,NULL,producer,NULL);
	pthread_create(&p2,NULL,producer,NULL);
	pthread_create(&c1,NULL,consumer,NULL);
	pthread_create(&c2,NULL,consumer,NULL);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	pthread_join(c1,NULL);
	pthread_join(c2,NULL);
}



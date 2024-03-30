#include<pthread.h>
#include<stdio.h>
//max=3,which means buffer has 3 resource slots
#define MAX 3
int buffer[MAX];
int fill_ptr=0;
int use_ptr=0;
int count=0;

void put(int value){
	buffer[fill_ptr]=value;
	fill_ptr=(fill_ptr+1)%MAX;
	count++;
	printf("has producd,now count=%d\n",count);
}

int get(){
	int tmp=buffer[use_ptr];
	use_ptr=(use_ptr+1)%MAX;
	count--;
	printf("has consumed,now count=%d\n",count);
	return tmp;
}

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t empty,fill=PTHREAD_COND_INITIALIZER;

void *producer(void *arg){
	while(1){
		pthread_mutex_lock(&mutex);
		while(count==MAX)
			pthread_cond_wait(&empty,&mutex);
		put(1);
		pthread_cond_signal(&fill);
		pthread_mutex_unlock(&mutex);
	}
}

void *consumer(void *arg){
	while(1){
		pthread_mutex_lock(&mutex);
		while(count==0)
			pthread_cond_wait(&fill,&mutex);
		get();
		pthread_cond_signal(&empty);
		pthread_mutex_unlock(&mutex);
	}
}

void main(){
	printf("begin\n");
	pthread_t p1,p2,c1,c2;
	//which means there are 2 producers and 2 consumers
	pthread_create(&p1,NULL,producer,NULL);
	pthread_create(&p2,NULL,producer,NULL);
	pthread_create(&c1,NULL,consumer,NULL);
	pthread_create(&c2,NULL,consumer,NULL);
	//there is no way that count<0 or count >3
	//the program wont stop,use ctrl+c to stop
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	pthread_join(c1,NULL);
	pthread_join(c2,NULL);
}

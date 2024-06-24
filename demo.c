#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

volatile int counter = 0;

typedef struct {
    int identifier;
    int numToIncrement;
} ThreadData;



void *mythread(void *arg)
{
	int index = 0;
	int status;

	ThreadData *data = (ThreadData *)arg;
	for(index = 0; index < data->numToIncrement; index++){
		status = pthread_mutex_lock(&mutex);
		if(status != 0){
			printf("Error in pthread_mutex_lock\n");
			exit(1);
		}
		counter++;
		printf("Thread %d: new value counter = %d\n", data->identifier, counter);
		status = pthread_mutex_unlock(&mutex);
		if(status != 0){
			printf("Error in pthread_mutex_unlock\n");
			exit(1);
		}
	}	
    return NULL;
}


int main(int argc, char *argv[])
{
    pthread_t p1, p2;
    int status;
	int numToIncrement = 1000;
    ThreadData data1, data2;

    data1.identifier = 1;
    data1.numToIncrement = numToIncrement;

    data2.identifier = 2;
    data2.numToIncrement = numToIncrement;

    status = pthread_create(&p1, NULL, mythread, &data1);
    if(status != 0){
	printf("Error in pthread_create\n");
	exit(1);
    }

    status = pthread_create(&p2, NULL, mythread, &data2);
    if(status != 0){
	printf("Error in pthread_create\n");
	exit(1);
    }

    status = pthread_join(p1, NULL);
    if(status != 0){
	printf("Error in pthread_join\n");
	exit(1);
    }

    status = pthread_join(p2, NULL);
    if(status != 0){
	printf("Error in pthread_join\n");
	exit(1);
    }

    printf("Counter value: %d\n", counter);

    return 0;
}


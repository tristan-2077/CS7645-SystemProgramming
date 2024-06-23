/* demo of producer-consumer problem without condition variable 
 * 1. number of units can not exceed MAX_BUFFER_SIZE
 * 2. number of units can not be negative
 *  problem: is busy waiting!
 *  solution: use condition variable!!!!
 * */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



#define MAX_BUFFER_SIZE 3
#define TRUE 1
#define FALSE 0

volatile int numberOfUnits = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


// Use condition variable to solve the problem
// wait and signal
// 1. wait is noblocking, it will yield the CPU to other threads
// 2. signal will wake up the waiting thread
// we still need mutex to protect the shared data



pthread_cond_t unitAvailable = PTHREAD_COND_INITIALIZER;

pthread_cond_t spaceAvailable = PTHREAD_COND_INITIALIZER;



void *producer(void *input)
{	

	int status;
    while (TRUE)
    {
	status = pthread_mutex_lock(&mutex);
	if (status != 0)
	{
	    printf("Error locking mutex\n");
	    exit(1);
	}
/*
	if (numberOfUnits < MAX_BUFFER_SIZE)
	{
	    numberOfUnits++;
	    printf("Producer: %d\n", numberOfUnits);
	}else{
		printf("Producer: Buffer is full\n");
	}
*/
	while(numberOfUnits >= MAX_BUFFER_SIZE){
		printf("Producer: waiting for space\n");
		status = pthread_cond_wait(&spaceAvailable, &mutex);
		if (status != 0)
		{
		    printf("Error waiting for condition variable\n");
		    exit(1);
		}


	}	
	numberOfUnits++;
	printf("Producer: %d\n", numberOfUnits);
	if(numberOfUnits == 1){
		// need to wake up the consumer;
		status = pthread_cond_signal(&unitAvailable);
		if (status != 0)
		{
		    printf("Error signaling condition variable\n");
		    exit(1);
		}

	}


	status = pthread_mutex_unlock(&mutex);
	if (status != 0)
	{
	    printf("Error unlocking mutex\n");
	    exit(1);
    }
	sleep(1);
	}
}


void *consumer(void *input)
{
	int status;
    while (TRUE)
    {
	status = pthread_mutex_lock(&mutex);
	if (status != 0)
	{
	    printf("Error locking mutex\n");
	    exit(1);
	}
/*
	if (numberOfUnits > 0)
	{
	    numberOfUnits--;
	    printf("Consumer: %d\n", numberOfUnits);
	}else{
		printf("Consumer: Buffer is empty\n");
	}
*/

	// USE CONDITION VARIABLE
	while(numberOfUnits==0){
		printf("Consumer: waiting for unit\n");
		status = pthread_cond_wait(&unitAvailable, &mutex);
		if (status != 0)
		{
		    printf("Error waiting for condition variable\n");
		    exit(1);
		}
	}
	numberOfUnits--;
	printf("Consumer: %d\n", numberOfUnits);
	if(numberOfUnits == MAX_BUFFER_SIZE-1){
		// need to wake up the producer;
		status = pthread_cond_signal(&spaceAvailable);
		if (status != 0)
		{
		    printf("Error signaling condition variable\n");
		    exit(1);
		}

	}




	status = pthread_mutex_unlock(&mutex);
	if (status != 0)
	{
	    printf("Error unlocking mutex\n");
	    exit(1);
    }
	sleep(2);
	}
}

int	main()
{
    pthread_t producerThread, consumerThread;
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);
}

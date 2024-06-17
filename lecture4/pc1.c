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

	if (numberOfUnits < MAX_BUFFER_SIZE)
	{
	    numberOfUnits++;
	    printf("Producer: %d\n", numberOfUnits);
	}else{
		printf("Producer: Buffer is full\n");
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

	if (numberOfUnits > 0)
	{
	    numberOfUnits--;
	    printf("Consumer: %d\n", numberOfUnits);
	}else{
		printf("Consumer: Buffer is empty\n");
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

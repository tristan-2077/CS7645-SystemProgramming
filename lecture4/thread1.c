/*
 *Compile using:
 * cc thread1.c -o thread1 -Werror -pthread 
 * link to pthread library
 */
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

// volatile means that the variable can be changed by other threads
//
//race condition occurs when two threads try to access the same variable
volatile int count = 0;

// declare a mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void* threadFunction(void *input)
{
		/* sleep for 2 seconds, fix warning
		 warning: implicit declaration of function ‘sleep’
		 to include unistd.h
			sleep(2);
		
			printf("I am the child thread\n");
		*/


	
		// mutex is a lock that can be locked and unlocked

		int status;
		if(input == NULL)
		{
				printf("Input is NULL\n");
				// stop the whole program not just the thread
				exit(1);
		}
		// go from void* to int*; interpret the input as an integer pointer
		int* pointerToInt = (int*)input;
		int numIncrements = *pointerToInt;
		for(int index = 0; index < numIncrements; index++)
		{
				status = pthread_mutex_lock(&mutex);
				if(status != 0)
				{
						printf("Error in locking mutex\n");
						exit(1);
				}
		
				count++;
				// mutex unlock
				status = pthread_mutex_unlock(&mutex);
				if(status != 0)
				{
						printf("Error in unlocking mutex\n");
						exit(1);
				}

		}


		pthread_exit(NULL);
}	


int main()
{
		pthread_t thread1, thread2;
		int status;
		void *result1, *result2;
		int cnt = 100000000;
		printf("Parent is about to create a child thread\n");

		/*
		 * parameters:
		 * 1. thread id
		 * 2. thread attributes (NULL for default)
		 * 3. thread function 
		 * 4. thread function arguments (NULL if no arguments)
		 */

		status = pthread_create(&thread1, NULL, threadFunction, (void*)&cnt);
		if(status != 0)
		{
				printf("Error in creating thread\n");
				exit(1);
		}	
		
		status = pthread_create(&thread2, NULL, threadFunction, (void*)&cnt);
		if(status != 0)
		{
				printf("Error in creating thread\n");
				exit(1);
		}

		// wait for the child thread to finish
		status = pthread_join(thread1, &result1);
		if(status != 0)
		{
				printf("Error in joining thread\n");
				exit(1);
		}	
		// wait for the child thread to finish
		status = pthread_join(thread2, &result2);
		if(status != 0)
		{
				printf("Error in joining thread\n");
				exit(1);
		}


		printf("Child thread has finished\n");

		// print the value of count
		printf("Count is %d\n", count);
		printf("Parent is about to exit\n");
}


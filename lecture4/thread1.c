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
volatile int count = 0;




void* threadFunction(void *input)
{
		/* sleep for 2 seconds, fix warning
		 warning: implicit declaration of function ‘sleep’
		 to include unistd.h
			sleep(2);
		
			printf("I am the child thread\n");
		*/
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
				count++;
		}

		pthread_exit(NULL);
}	


int main()
{
		pthread_t thread;
		int status;
		void* result;
		int cnt = 10;
		printf("Parent is about to create a child thread\n");

		/*
		 * parameters:
		 * 1. thread id
		 * 2. thread attributes (NULL for default)
		 * 3. thread function 
		 * 4. thread function arguments (NULL if no arguments)
		 */

		status = pthread_create(&thread, NULL, threadFunction, &cnt);
		if(status != 0)
		{
				printf("Error in creating thread\n");
				exit(1);
		}	

		// wait for the child thread to finish
		status = pthread_join(thread, &result);
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


#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

/* Goals:
 * Parent process creates a child process
 * Child process run ls -l
 * Parent process prints its PID and the PID of the child
 * Child process runs a new program using execv
 * Parent process waits for the child to finish
 *
 */

void printBye(){
	// Process exit handler
	printf("Goodbye from process %d\n", getpid());
}
int main(){
	pid_t child_pid;
	int childStatus, status;

	//child_pid = fork();
	//register exit event
	status = atexit(printBye);
	

	if(status != 0){
		printf("Error registering exit event\n");
		exit(1);
	}

	child_pid = fork();


	switch(child_pid){
		case -1:
			printf("Error creating child process\n");
			break;
		case 0:
			/*
			printf("Child PID: %d\n", getpid());
			char *args[] = {"./hello", NULL};
			execv(args[0], args);
			break;*/
			//print id and parent id
			printf("Child PID: %d\n, My parent PID is %d", getpid(), getppid());
			
			// use execve
			//sleep(2);
			execlp("/bin/ls", "ls", "-l", NULL);
			// Code should NEVER reach here

			printf("Error running execv\n");
			_exit(0);


		default:
			printf("I am the parent%d , my child is %d\n", getpid(), child_pid);

			//wait for child to finish
			child_pid = wait(&childStatus);
			if(child_pid == -1){
				printf("Error waiting for child process\n");
				exit(1);
			}
			printf("Child process finished with status %d\n", WEXITSTATUS(childStatus));
			//print child status
			break;
	}

}



/*
 *
 * Copies one file (the source) to another (the destination)
 * Compile using:
 *
 * cc filecopy.c -o filecopy
 *
 * Run using:
 *
 * ./filecopy source destination
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>


#define CHUNK_SIZE 10


int main(int argc, char* argv[])
{

	int  sourceFd, destinationFd;
	int numRead, numWritten;
	int status;
	char buffer[CHUNK_SIZE];

	/* Command line validation */
        if(argc != 3 ||
		strcmp(argv[1], "-h") == 0 || strcmp(argv[1] , "--help") == 0 )
	{
		printf("Usage: %s source destination\n", argv[0]);
		exit(1);
	}
	/* Open the source file */
	
	sourceFd = open(argv[1], O_RDONLY);
	if(-1 == sourceFd){
		printf("open file error");
		perror("Error:");
	}
	
	

	destinationFd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IXUSR
			); 
	numRead = read(sourceFd, buffer, CHUNK_SIZE);
	while(numRead > 0){
		numWritten = write(destinationFd, buffer, numRead);
		if(numWritten < numRead)
		{
			printf("Partial write error\n");
			exit(1);
		}
		numRead = read(sourceFd, buffer, CHUNK_SIZE);
	}
	if(numRead == -1)
	{
		printf("Failed to read from source file.\n");
		exit(1);
	}	

	// O_TRUNC means rewrite exists file to empty 
	// O_APPEND means add to tail
	
	

	if(-1 == destinationFd){
		printf("open file error");
		perror("Error:");
	}




	/* Read from source to RAM and write from RAM to destinaiton */

	/* Close the source file */
	status = close(sourceFd);
	if(status == -1){
		printf("Failed to cloase the source file.\n");
	}	
	close(destinationFd);


	












	/* Close the source file */

	/* Close the destination file */









}

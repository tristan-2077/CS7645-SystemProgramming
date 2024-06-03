/*
 * Compile using
 * cc stringtransform.c -o stringtransform
 * Run using:
 * ./stringtranform message
 * For example, if we run: ./stringtransform LinuxProgramming,
 * the program should print: LINUXPROGRAMMING
 *
 */
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 100

int converToa(int input)
{
	return 'a';

}
void stringToupper(char* message)
{
	int index;
	if(message == NULL)
	{
		printf("message cannot be NULL\n");
		exit(1);
	
	}


	for(index = 0; message[index] != '\0'; index++)
	{
		message[index] = toupper(message[index]);
	
	}

}

// pointer for a function 
void transform(char* message, int (*visitor)(int) ){

        int index;
        if(message == NULL)
        {
                printf("message cannot be NULL\n");
                exit(1);

        }


        for(index = 0; message[index] != '\0'; index++)
        {
                message[index] = visitor(message[index]);

        }




}
int main(int argc, char* argv[]){
	char message[MAX_SIZE];

	if(argc != 2|| strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
	{
	
		printf("Usage: %s message\n", argv[0]);
		exit(1);
	}
	strcpy(message, argv[1]);
	printf("Before: %s\n", message);
	//stringToupper(message);
	transform(message, toupper);
	printf("After: %s\n", message);
	transform(message, tolower);
	printf("After: %s\n", message);
	transform(message, converToa);
	printf("After convert to a: %s", message);
	exit(0);

}

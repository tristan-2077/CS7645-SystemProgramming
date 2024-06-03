#include<stdlib.h>
#include<string.h>
#include<stdio.h>

typedef struct Person
{

	char firstName[20];
	char lastName[20];
} Person;
// typedef



void swapIntegers(int* px, int* py){
	int tmp;
	tmp = *px;
	*px = *py;
	*py = tmp;

}


void swapPersons(Person* px, Person* py){
	Person tmp;
	tmp = *px;
	*px = *py;
	*py = tmp;
}

int main(int argc, char* argv[]){
	if(argc != 3 ||
		strcmp(argv[1], "-h") == 0 ||
		strcmp(argv[1], "--help") == 0){
		printf("Usage: %s", "-h");
	
	}
	int x = atoi(argv[1]);
	int y = atoi(argv[2]);

	printf("Before swap: %d %d\n", x, y);
	swapIntegers(&x, &y);
	printf("After swap: %d %d\n", x, y);
	
	Person p1 = {"Jack", "Ali"};
	Person p2 = {"Tom", "H"};
	printf("Before swap p1:%s,%s, p2: %s,%s\n", p1.firstName, p1.lastName, p2.firstName, p2.lastName);	
 	swapPersons(&p1, &p2);	
	printf("After swap p1:%s,%s, p2: %s,%s\n", p1.firstName, p1.lastName, p2.firstName, p2.lastName);	
	exit(0);
}

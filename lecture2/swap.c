#include<stdlib.h>
#include<string.h>
#include<stdio.h>

void swap(int* x, int* y){
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;

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
	swap(&x, &y);
	printf("After swap: %d %d\n", x, y);
	exit(0);
}

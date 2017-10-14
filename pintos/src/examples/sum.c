#include <syscall.h>
#include <stdio.h>
#include <stdlib.h>

#define INT_ARG(i)	\
	atoi(argv[i+1])
int main(int argc, char *argv[]) {
	printf("sum\n");
	if( argc != 5 ){
		printf("Usage : ./sum [num 1] [num 2] [num 3] [num 4]\n");
		exit(1);
	}
	printf("%d %d\n", pibonacci(INT_ARG(0)), sum_of_four_integers(INT_ARG(0), INT_ARG(1), INT_ARG(2), INT_ARG(3)));
	return EXIT_SUCCESS;
}

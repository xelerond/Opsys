//Robbie Henderson - H00011358
#include "super_malloc.h"
#include <stdlib.h>
#include <stdio.h>
int main()
{
	/*The test program is very simply setting a pointer to the address of the current end of block
	and printing the address
	the program will use the created malloc, print pointer
	then free and print again
	simple but hopefully effective*/
	void * pointer = super_malloc(sizeof(char));
	printf("allocating memory....\naddress: %li\n\n", (size_t)pointer);
	pointer = super_mfree(pointer);
	printf("freeing memory....\naddress: %li\n", (size_t)pointer);
	return 0;
}

#include "super_malloc.h"
#include <stdlib.h>
#include <stdio.h>
int main()
{
	void * pointer = super_malloc(sizeof(char));
	printf("allocating memory....\naddress: %li\n\n", (size_t)pointer);
	pointer = super_mfree(pointer);
	printf("freeing memory....\naddress: %li\n", (size_t)pointer);
	return 0;
}

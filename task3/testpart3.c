#include "super_malloc.h"
#include <stdio.h>

int main (int argc, char * argv[])
{
	printf("mallocing\n%d\n", super_malloc(100));
	return 0;
}
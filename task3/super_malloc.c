#include <sys/types.h>
#include <stdio.h>

int super_malloc (size_t size)
{
	printf("%d\n", sbrk(0));
	sbrk(size);
	printf("%d\n", sbrk(0));
	return 0;
}
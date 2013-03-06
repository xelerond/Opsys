#include "super_malloc.h"
#include <stdlib.h>
#include <stdio.h>
int main()
{
	int counter;
	void * pointer;
	int d = 1;
	for(counter = 1; counter > 0; counter += d)
	{
		pointer = super_malloc(sizeof(int)*counter);
		printf("%lu\n", (size_t)pointer);
		if(pointer != NULL)
		{
			super_mfree(pointer);
			if(counter == 10)
			{
				d = -1;
			}
		}
	}
	return 0;
}

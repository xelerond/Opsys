//Robbie Henderson - H00011358

#include <unistd.h>
#include <stdio.h>

int gig = 1073741824;

struct chunk_info
{
	size_t size;
	int on;
	struct chunk_info * next;
	struct chunk_info * prev;
};

static struct chunk_info * start = NULL;

size_t chunk_size = sizeof(struct chunk_info);


void * super_malloc(size_t size)
{
	if(start == NULL)
	{
		start = (struct chunk_info *) sbrk(gig);
		struct chunk_info * next  = (struct chunk_info*)(((char*)start) + chunk_size);
		
		next->size = gig - size - (2*chunk_size);
		next->on = 0;
		next->prev = NULL;
		next->next = NULL;
		start->size = size;
		start->on = 1;
		start->prev = NULL;
		start->next = next;
		return (struct chunk_info*)(((char*)start) + chunk_size);
	}
	struct chunk_info *new = start;
	while(new->next != NULL)
	{
		if(new->on == 0 && new->size >= size)
		{
			new->on = 1;
			
			return (struct chunk_info*)(((char*)new) + chunk_size);
		}
		new = new->next;
	}
	if(new->size < (size + chunk_size)) return NULL;
	struct chunk_info * next = (struct chunk_info*)(((char*)new)+ chunk_size);
	next->size = new->size - size - chunk_size;
	next->on = 0;
	next->next = NULL;
	new->size = size;
	new->on = 1;
	new->next = next;
	return (struct chunk_info*)(((char*)new) + chunk_size);
}


void super_mfree(void * object)
{
	struct chunk_info * new = (struct chunk_info*)(((char*)object) -chunk_size);
	new->on = 0;
	
}
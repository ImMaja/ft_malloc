#include "../include/alloc.h"

void	*realloc(void *ptr, size_t size)
{
	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}

	
	return (NULL);
}

#include "alloc_internal.h"


void	*realloc(void *ptr, size_t size)
{
	void	*internal_ret = NULL;

	if (!ptr)
		return (malloc(size));

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (normalize_size(&size) == -1)
		return (NULL);

	if (pthread_mutex_lock(get_alloc_mutex()) != 0)
		return (NULL);

	internal_ret = realloc_internal(ptr, size);

	pthread_mutex_unlock(get_alloc_mutex());
	return (internal_ret);
}

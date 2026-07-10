#include "alloc_internal.h"

void	*malloc(size_t size)
{
	void	*internal_ret = NULL;

	if (normalize_size(&size) == -1)
		return (NULL);

	if (pthread_mutex_lock(get_alloc_mutex()) != 0)
		return (NULL);

	internal_ret = malloc_internal(size);

	pthread_mutex_unlock(get_alloc_mutex());
	return (internal_ret);
}

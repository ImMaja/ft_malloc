#include "alloc_internal.h"


void	free(void *ptr)
{
	if (!ptr)
		return ;

	if (pthread_mutex_lock(get_alloc_mutex()) != 0)
		return ;

	free_internal(ptr);
	pthread_mutex_unlock(get_alloc_mutex());
}

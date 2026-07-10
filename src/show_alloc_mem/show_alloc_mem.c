#include "alloc_internal.h"


void	show_alloc_mem(void)
{
	if (pthread_mutex_lock(get_alloc_mutex()) != 0)
		return ;

	show_alloc_mem_internal();
	pthread_mutex_unlock(get_alloc_mutex());
}

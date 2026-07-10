#include <unistd.h>

#include "alloc_internal.h"


static t_allocator	g_alloc = {
	.zones = NULL,
	.page_size = 0,
	.alloc_mutex = PTHREAD_MUTEX_INITIALIZER
};


t_zone	**get_zones(void)
{
	return (&g_alloc.zones);
}


size_t	get_page_size(void)
{
	long	page_size;

	if (g_alloc.page_size != 0)
		return (g_alloc.page_size);

	page_size = sysconf(_SC_PAGESIZE);
	if (page_size <= 0)
		return (0);

	g_alloc.page_size = (size_t) page_size;
	return (g_alloc.page_size);
}


pthread_mutex_t	*get_alloc_mutex(void)
{
	return (&g_alloc.alloc_mutex);
}

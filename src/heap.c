#include <unistd.h>

#include "../include/alloc.h"

static t_heap	g_heap = {NULL, NULL, NULL};

/**
 * @brief Getter of heap struct
 */
t_heap	*get_heap(void)
{
	return (&g_heap);
}

/**
 * @brief Return pointer of corresponding linked-list type
 * if type is TINY, return &heap->tiny
 * ...
 * @param type The enum type
 * @return Ptr to a heap zone
 */
t_zone	**get_zone_ptr_by_type(const t_zone_type type)
{
	t_heap	*heap = get_heap();

	if (type == TINY)
		return (&heap->tiny);
	else if (type == SMALL)
		return (&heap->small);
	else if (type == LARGE)
		return (&heap->large);
	return (NULL);
}
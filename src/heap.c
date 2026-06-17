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
 * if type is TINY, return heap->tiny
 * ...
 * @param type The enum type
 * @return Beginning of a zone linked-list
 */
t_zone	*get_zone_ptr_by_type(const t_zone_type type)
{
	t_heap	*heap = get_heap();

	switch (type)
	{
		case TINY:
			return (heap->tiny);
		case SMALL:
			return (heap->small);
		case LARGE:
			return (heap->large);
	}

	// Should nerver happend
	return (NULL);
}
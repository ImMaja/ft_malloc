#include <stdint.h>

#include "../ft_printf/ft_printf.h"
#include "../include/alloc.h"


/**
 * @brief Get the type of a zone in a string
 * ex: TINY -> "TINY"
 */
static char	*get_str_type(const t_zone_type type)
{
	if (type == TINY)
		return ("TINY");
	else if (type == SMALL)
		return ("SMALL");
	else if (type == LARGE)
		return ("LARGE");
	return ("wtf?");
}


/**
 * @brief Iterate on all t_zone linked-list to find the
 * next zone by incresing memory address
 * @param heap The struct containing all t_zone linked-list
 * @param last The previous zone address
 */
static t_zone	*find_next_zone(const t_heap *heap, const uintptr_t last)
{
	t_zone		*zones[HEAP_ELEM] = {
		heap->tiny,
		heap->small,
		heap->large
	};
	t_zone		*iter = NULL;
	t_zone		*best = NULL;
	uintptr_t	best_addr = UINTPTR_MAX;

	for (uint8_t i = 0 ; i < HEAP_ELEM ; i++)
	{
		iter = zones[i];
		while (iter)
		{
			if ( (uintptr_t) iter > last && (uintptr_t) iter < best_addr )
			{
				best = iter;
				best_addr = (uintptr_t) iter;
			}
			iter = iter->next;
		}
	}

	return (best);
}


/**
 * 
 */
void	show_alloc_mem(void)
{
	t_heap	*heap = get_heap();

	

	size_t	total_alloc_size = 0;
}

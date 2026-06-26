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
	t_zone		*z = NULL;
	t_zone		*best = NULL;
	uintptr_t	best_addr = UINTPTR_MAX;

	for (uint8_t i = 0 ; i < HEAP_ELEM ; i++)
	{
		z = zones[i];
		while (z)
		{
			if ( (uintptr_t) z > last && (uintptr_t) z < best_addr )
			{
				best = z;
				best_addr = (uintptr_t) z;
			}
			z = z->next;
		}
	}

	return (best);
}


/**
 * @brief Show all allocated zone
 */
void	show_alloc_mem(void)
{
	t_heap		*heap = get_heap();
	uintptr_t	last = 0;
	t_zone		*z = NULL;
	t_block		*b = NULL;
	size_t		total_alloc = 0;

	while ( ( z = find_next_zone(heap, last) ) != NULL )
	{
		ft_printf("%s : %p\n", get_str_type(z->type), z);
		b = z->blocks;
		if (!b)
			ft_printf("No block in this zone, that should not happend ?\n");
		while (b)
		{
			if (b->free == 0)
			{
				ft_printf("%p - %p : %d bytes\n", (uintptr_t) b + BLOCK_HEADER_SIZE, (uintptr_t) b + BLOCK_HEADER_SIZE + b->payload_size, b->payload_size);
				total_alloc += b->payload_size;
			}
			b = b->next;
		}
		last = (uintptr_t) z;
	}
	ft_printf("Total : %d bytes\n", total_alloc);
}

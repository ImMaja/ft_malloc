#include <unistd.h>

#include "../ft_printf/ft_printf.h"
#include "../include/alloc.h"

void	*malloc(size_t size)
{
	ft_printf("malloc called -------------------------\n");

	t_zone_type	alloc_type;

	if (size > SMALL_BLOCK_SIZE)
	{
		ft_printf("malloc is a LARGE allocation\n");
		alloc_type = LARGE;
	}
	else if (size > TINY_BLOCK_SIZE && size < SMALL_BLOCK_SIZE)
	{
		ft_printf("malloc is a SMALL allocation\n");
		alloc_type = SMALL;
	}
	else
	{
		ft_printf("malloc is a TINY allocation\n");
		alloc_type = TINY;
	}

	t_zone	*zone = create_new_zone(alloc_type, size);
	ft_printf("zone ptr: %p\n", zone);

	t_heap	*heap = get_heap();

	if (heap->tiny == NULL)
		ft_printf("heap->tiny is NULL\n");
	else
		ft_printf("heap->tiny is NOT NULL\n");

	if (heap->small == NULL)
		ft_printf("heap->small is NULL\n");
	else
		ft_printf("heap->small is NOT NULL\n");

	if (heap->large == NULL)
		ft_printf("heap->large is NULL\n");
	else
		ft_printf("heap->large is NOT NULL\n");

	ft_printf("zone->type: %d\n", zone->type);
	ft_printf("zone->size: %d\n", zone->size);
	ft_printf("zone->blocks: %p\n", zone->blocks);
	ft_printf("zone->next: %p\n", zone->next);
	ft_printf("zone->prev: %p\n", zone->prev);

	return (NULL);
}

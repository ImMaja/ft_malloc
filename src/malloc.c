#include <unistd.h>

#include "../ft_printf/ft_printf.h"
#include "../include/alloc.h"

/**
 * 
 */
void	*malloc(size_t size)
{
	ft_printf("malloc called -------------------------\n");
	// Check if size is LARGE type
	if (size >= SMALL_BLOCK_SIZE)
	{
		ft_printf("malloc is a LARGE allocation ----------\n");
		int	ret = create_new_zone(LARGE, size);
		ft_printf("create_new_zone() returned: %d\n", ret);

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

		ft_printf("heap->large->type: %d\n", heap->large->type);
		ft_printf("heap->large->size: %d\n", heap->large->size);
		ft_printf("heap->large->blocks: %p\n", heap->large->blocks);
		ft_printf("heap->large->next: %p\n", heap->large->next);
		ft_printf("heap->large->prev: %p\n", heap->large->prev);
	}

	return (NULL);
}

#include <unistd.h>

#include "../ft_printf/ft_printf.h"
#include "../include/alloc.h"

void	*malloc(size_t size)
{
	ft_printf("malloc called with size %u -------------------------\n", size);

	t_zone_type	alloc_type;

	if (size > SMALL_BLOCK_SIZE)
		alloc_type = LARGE;
	else if (size > TINY_BLOCK_SIZE && size < SMALL_BLOCK_SIZE)
		alloc_type = SMALL;
	else
		alloc_type = TINY;

	t_zone	*zone = create_new_zone(alloc_type, size);
	ft_printf("zone ptr: %p\n", zone);


	return (NULL);
}

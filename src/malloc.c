#include <unistd.h>

#include "../ft_printf/ft_printf.h"
#include "../include/alloc.h"

void	*malloc(size_t size)
{
	ft_printf("malloc called with size %u -------------------------\n", size);

	t_zone_type	type;
	t_heap		*heap = get_heap();
	t_zone		*zone = NULL;

	/** Align size to 16, ex: 1000 -> 1008 */
	size = ALIGN_UP(size);

	if (size > SMALL_BLOCK_SIZE)
		type = LARGE;
	else if (size > TINY_BLOCK_SIZE && size < SMALL_BLOCK_SIZE)
		type = SMALL;
	else
		type = TINY;

	/** New alloc is a LARGE allocation */
	if (type == LARGE)
	{
		/** Create a new zone */
		t_zone	*zone = create_new_zone(type, size);

		/** Ptr to the default block of new zone */
		t_block	*default_block_ptr = (t_block *) zone + ZONE_HEADER_SIZE;

		/** Create a new block in the new zone */
		void	*payload = split_block(default_block_ptr, size);

		return (payload);
	}

	zone = get_zone_ptr_by_type(type);
	t_block	*split_block = find_available_block(zone, size);
	if (!split_block)
	{
		zone = create_new_zone(type, size);
		if (!zone)
			return (NULL);
		
	}

	return (NULL);
}

#include <unistd.h>

#include "../ft_printf/ft_printf.h"
#include "../include/alloc.h"


void	*malloc(size_t size)
{
	ft_printf("malloc called with size %u -------------------------\n", size);

	t_zone_type	type = get_zone_type_by_size(size);
	t_zone		*zone = NULL;
	t_block		*split = NULL;
	void		*payload = NULL;

	// Align size to 16, ex: 1000 -> 1008
	size = ALIGN_UP(size);

	// New alloc is a LARGE allocation
	// Create a zone and a default block for the alloc
	if (type == LARGE)
	{
		t_zone	*zone = create_new_zone(type, size);
		if (!zone)
			return (NULL);
		
		split = (t_block *) ( (char *) zone + ZONE_HEADER_SIZE );
		split->payload_size = size;
		return ((char *) split + BLOCK_HEADER_SIZE);
	}
	// New alloc is a TINY or SMALL allocation
	// Try to find an available block for the allocation
	// If no available block, create a new zone and a default block
	zone = *get_zone_ptr_by_type(type);
	split = find_available_block(zone, size);
	if (!split)
	{
		zone = create_new_zone(type, size);
		if (!zone)
			return (NULL);
		split = (t_block *) ( (char *) zone + ZONE_HEADER_SIZE );
	}

	// Split available block for the new allocation
	payload = split_block(split, size);

	return (payload);
}

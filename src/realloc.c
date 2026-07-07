#include "../include/alloc.h"

void	*realloc(void *ptr, size_t size)
{
	t_zone		*zone = NULL;
	t_block		*block	= NULL;
	t_zone_type	old_zone_type = 0;
	t_zone_type	new_zone_type = 0;
	void		*new_ptr = NULL;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}

	zone = find_zone_from_payload_ptr(ptr);
	// Not an address from my allocator, wtf bro?
	if (!zone)
		return (NULL);

	block = find_block_from_payload_ptr(zone, ptr);
	// Not a valid payload address, again wtf?
	if (!block)
		return (NULL);

	// Block is already freed
	if (block->free)
		return (NULL);

	size = ALIGN_UP(size);
	old_zone_type = zone->type;
	new_zone_type = get_zone_type_by_size(size);

	// Same size as current block size
	if (size == block->payload_size)
		return (ptr);


	// Shrink cases,
	// new size is smaller then current payload_size
	if (size < block->payload_size)
	{
		// Difference is not enought for a free block, no changes
		if (block->payload_size - size < MIN_SPLIT_SIZE)
			return (ptr);

		split_block(block, size);
		return (ptr);
	}

	// Grow cases
	// New size is bigger then current payload_size

	// If new size upgrade the allocation type
	if (new_zone_type > old_zone_type)
	{
		new_ptr = malloc(size);
		if (!new_ptr)
			return (NULL);
		ft_memcpy(new_ptr, ptr, block->payload_size);
		free(ptr);
		return (new_ptr);
	}

	// New size does not upgrade the allocation type
	
	// Ici agrandir le block
	// si pas possible, malloc, memcpy et free
	

	return (NULL);
}

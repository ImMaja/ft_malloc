#include "../include/alloc.h"

static void	free_internal(t_zone *zone, t_block *block);


void	free(void *ptr)
{
	t_zone		*zone = NULL;
	t_block		*block = NULL;

	// Not an address from my allocator
	zone = find_zone_from_payload_ptr(ptr);
	if (!zone)
		return ;

	// Not a valid payload address
	block = find_block_from_payload_ptr(zone, ptr);
	if (!block)
		return ;

	// Block is already freed
	if (block->free)
		return ;

	free_internal(zone, block);
}

static void	free_internal(t_zone *zone, t_block *block)
{
	t_zone	*other_empty = NULL;

	// Munmap the zone for LARGE allocation
	if (zone->type == LARGE)
	{
		delete_zone(zone);
		return ;
	}

	// If its the last block in the zone
	if (zone->used_blocks == 1)
	{
		// Check if we delete the zone by checking if there is
		// an another empty zone of the same type
		other_empty = find_empty_zone(zone->type, zone);
		if (other_empty)
		{
			if (delete_zone(zone) == 0)
				return ;
		}
	}
	block->free = 1;
	zone->used_blocks--;
	merge_free_blocks(block);
}

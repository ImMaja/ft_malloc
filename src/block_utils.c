#include "../include/alloc.h"

t_block	*find_free_block(const t_zone_type type, const size_t size)
{
	t_zone	*zone;
	t_block	*block;

	zone = *get_zones();
	while (zone)
	{
		if (zone->type == type)
		{
			block = zone->blocks;
			while (block)
			{
				if (block->free && block->payload_size >= size)
					return (block);
				block = block->next;
			}
		}
		zone = zone->next;
	}
	return (NULL);
}

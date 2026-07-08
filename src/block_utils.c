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

/**
 * @brief Merge consecutive free blocks near 'free_block'
 * @param free_block Pointer to a free block
 */
void	merge_free_blocks(t_block *block)
{
	if (!block || !block->free)
		return ;

	// Find first free block
	while (block->prev && block->prev->free)
		block = block->prev;

	while (block->next && block->next->free)
	{
		block->payload_size += BLOCK_HEADER_SIZE + block->next->payload_size;
		if (block->next->next)
			block->next->next->prev = block;
		block->next = block->next->next;
	}
}

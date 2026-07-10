#include <stdint.h>

#include "../include/alloc.h"

/**
 * @brief Search a free block of at least 'size' size
 * and of corresponding zone type.
 * This function set zone and block in *out_zone and *out_block ptrs.
 * If no block found, *out_zone and *out_block are set to NULL
 * @param type Type of the zone
 * @param size Minimal size block
 * @param out_zone Pointer to zone pointer
 * @param out_block Pointer to block pointer
 * @return 0 if available block found, -1 otherwise
 */
int	find_free_block(const t_zone_type type, const size_t size, t_zone **out_zone, t_block **out_block)
{
	t_zone	*zone;
	t_block	*block;

	*out_zone = NULL;
	*out_block = NULL;

	zone = *get_zones();
	while (zone)
	{
		if (zone->type == type)
		{
			block = zone->blocks;
			while (block)
			{
				if (block->free && block->payload_size >= size)
				{
					*out_zone = zone;
					*out_block = block;
					return (0);
				}
				block = block->next;
			}
		}
		zone = zone->next;
	}
	return (-1);
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


/**
 * @brief Find the block of the given 'payload_ptr' in the zone 'zone'
 * If 'payload_ptr' is not a valid payload ptr given by malloc,
 * this function will return NULL
 * @param zone The zone of the 'payload_ptr' block
 * @param payload_ptr The payload ptr of a block
 * @return Block ptr if 'ptr' is valid, NULL otherwise
 */
t_block	*find_block_from_payload_ptr(const t_zone *zone, const void *payload_ptr)
{
	uintptr_t	payload_addr;
	uintptr_t	block_addr;
	t_block		*b;

	if (!zone || !payload_ptr)
		return (NULL);

	payload_addr = (uintptr_t) payload_ptr;
	if (payload_addr < (uintptr_t) zone + BLOCK_HEADER_SIZE)
		return (NULL);

	block_addr = payload_addr - BLOCK_HEADER_SIZE;

	if (block_addr < (uintptr_t) zone)
		return (NULL);
	if ( block_addr >= (uintptr_t) ( (char *) zone + zone->size ) )
		return (NULL);

	b = zone->blocks;
	while (b)
	{
		if ( (uintptr_t) b == block_addr )
			return (b);
		b = b->next;
	}
	return (NULL);
}

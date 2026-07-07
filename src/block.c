#include <unistd.h>

#include "../include/alloc.h"

/**
 * @brief Create a default block in a new zone
 * Default blok will use all memory available in the zone
 * @param zone The zone who need a default block
 */
void	create_default_block(t_zone *zone)
{
	t_block	*b = (t_block *) ( (char *) zone + ZONE_HEADER_SIZE );

	zone->blocks = b;
	b->payload_size = zone->size - ZONE_HEADER_SIZE - BLOCK_HEADER_SIZE;
	b->free = 0;
	b->next = NULL;
	b->prev = NULL;
}


/**
 * @brief REFAIRE CETTE FONCTION je pense -------------------------------------------------
 * faut reflechir a comment utiliser un block free qui a asser de size mais pas asser pour split
 * le if est chelou on perd de la memoire
 */
t_block	*find_available_block(const t_zone *zone, const size_t size)
{
	t_block	*b = NULL;

	while (zone)
	{
		b = zone->blocks;
		while (b)
		{
			if (b->free && b->payload_size >= size + BLOCK_HEADER_SIZE + MIN_PAYLOAD_SIZE)
				return (b);
			b = b->next;
		}
		zone = zone->next;
	}

	return (NULL);
}

/**
 * @brief Split a block and create a free remainder block
 * @param block The block to split
 * @param size The aligned size of the new block
 */
void	split_block(t_block *block, const size_t size)
{
	t_block	*new_next = NULL;
	t_block	*old_next = NULL;

	if (!block)
		return ;
	if (size >= block->payload_size)
		return ;
	if (block->payload_size - size < MIN_SPLIT_SIZE)
		return ;

	new_next = (t_block *) ( (char *) block + BLOCK_HEADER_SIZE + size );
	old_next = block->next;

	block->next = new_next;
	new_next->prev = block;

	new_next->payload_size = block->payload_size - BLOCK_HEADER_SIZE - size;
	new_next->free = 1;
	new_next->next = old_next;
	if (old_next)
		old_next->prev = new_next;

	block->payload_size = size;
	block->free = 0;

	// Merge the two next blocks if they are both free
	merge_free_blocks(new_next);
}

#include "../include/alloc.h"

/**
 * @brief Create a default block in a new zone
 * Default blok will use all available memory in the zone
 * @param zone The zone who need a default block
 */
void	create_default_block(t_zone *zone, const size_t size)
{
	t_block	*block;

	if (!zone)
		return ;

	block = (t_block *) ( (char *) zone + ZONE_HEADER_SIZE );
	if (zone->type == LARGE)
		block->payload_size = size;
	else
		block->payload_size = zone->size - ZONE_HEADER_SIZE - BLOCK_HEADER_SIZE;
	block->free = 1;
	block->next = NULL;
	block->prev = NULL;

	zone->blocks = block;
}

/**
 * @brief Split 'block' with new size if possible,
 * create free block after with remaing memory
 * @param block The block to split
 * @param size The aligned size of the new block
 */
void	split_block(t_block *block, const size_t size)
{
	t_block	*new_next;
	t_block	*old_next;

	if (!block)
		return ;
	if (size >= block->payload_size)
		return ;
	if (block->payload_size - size < MIN_SPLIT_SIZE)
		return ;

	old_next = block->next;

	new_next = (t_block *) ( (char *) block + BLOCK_HEADER_SIZE + size );
	new_next->payload_size = block->payload_size - size - BLOCK_HEADER_SIZE;
	new_next->free = 1;
	new_next->prev = block;
	new_next->next = old_next;

	if (old_next)
		old_next->prev = new_next;

	block->payload_size = size;
	block->next = new_next;

	merge_free_blocks(new_next);
}

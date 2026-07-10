#include "../include/alloc.h"

/**
 * @brief Create a default block in a new zone
 * Default blok will use all available memory in the zone
 * @param zone The zone who need a default block
 * @return 0 on succes, -1 otherwise
 */
int	create_default_block(t_zone *zone)
{
	t_block	*block;
	size_t	block_size = 0;

	if (!zone)
		return (-1);
	if (zone->size < ZONE_HEADER_SIZE + BLOCK_HEADER_SIZE + MIN_PAYLOAD_SIZE)
		return (-1);

	block_size = zone->size - ZONE_HEADER_SIZE - BLOCK_HEADER_SIZE;

	block = (t_block *) ( (char *) zone + ZONE_HEADER_SIZE );
	block->payload_size = block_size;
	block->free = 1;
	block->next = NULL;
	block->prev = NULL;

	zone->blocks = block;

	return (0);
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
	if (block->payload_size - size < MIN_BLOCK_SIZE)
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


/**
 * @brief Try to grow an existing block using the next free block.
 * If enough memory remains, create a new free block.
 * Otherwise, consume the whole next free block.
 * @param block The block to grow.
 * @param new_size The requested aligned new payload size.
 * @return 0 on success, -1 otherwise.
 */
int	inplace_grow(t_block *block, const size_t new_size)
{
	size_t	diff_size = 0;
	size_t	free_total_size = 0;
	size_t	remaining_size = 0;
	t_block	*old_next = NULL;
	t_block	*old_next_next = NULL;
	t_block	*new_next = NULL;

	// Check if next block exist and is free
	if (!block || !block->next || !block->next->free)
		return (-1);
	// Check if new_size is actually bigger then current payload_size
	if (new_size <= block->payload_size)
		return (-1);

	old_next = block->next;
	old_next_next = old_next->next;

	diff_size = new_size - block->payload_size;
	free_total_size = BLOCK_HEADER_SIZE + old_next->payload_size;

	// Check if next block is big enough to grow this one
	if (free_total_size < diff_size)
	return (-1);

	// At this point we can grow the block

	remaining_size = free_total_size - diff_size;

	// Check if we can create a new free block with remaining memory
	if (remaining_size >= MIN_BLOCK_SIZE)
	{
		new_next = (t_block *) ( (char *) block + BLOCK_HEADER_SIZE + new_size );

		new_next->payload_size = remaining_size - BLOCK_HEADER_SIZE;
		new_next->free = 1;
		new_next->prev = block;
		new_next->next = old_next_next;

		if (old_next_next)
			old_next_next->prev = new_next;

		block->payload_size = new_size;
		block->next = new_next;

		return (0);
	}

	// We cannot create a free block with remaining memory,
	// so we consume the whole free block

	block->payload_size += free_total_size;
	block->next = old_next_next;
	if (old_next_next)
		old_next_next->prev = block;

	return (0);
}

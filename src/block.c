#include <stdint.h>

#include "../include/alloc.h"

static void	merge_free_blocks(t_block *block);


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
 * @brief Search a free block of at least 'size' size and
 * of corresponding zone type
 * @param type Type of the zone
 * @param size Minimal size block
 * @return Pointer to the first corrsponding block,
 * NULL is no block was found
 */
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
 * @brief Merge consecutive free blocks near 'free_block'
 * @param free_block Pointer to a free block
 */
static void	merge_free_blocks(t_block *block)
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
 * @brief Try to grow an existing block using the next free block.
 * If enough memory remains, create a new free block.
 * Otherwise, consume the whole next free block.
 * @param block The block to grow.
 * @param new_size The requested aligned new payload size.
 * @return 0 on success, 1 on failure.
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
		return (1);
	// Check if new_size is actuallt bigger then current payload_size
	if (new_size <= block->payload_size)
		return (1);

	old_next = block->next;
	old_next_next = old_next->next;

	diff_size = new_size - block->payload_size;
	free_total_size = BLOCK_HEADER_SIZE + old_next->payload_size;

	// Check if next block is big enough to grow this one
	if (free_total_size < diff_size)
		return (1);

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

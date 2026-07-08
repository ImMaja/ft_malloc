#include "../include/alloc.h"

static void		*malloc_internal(const size_t size);
static t_block	*get_free_block_for_alloc(const t_zone_type type, const size_t size);
static void		*get_payload_addr(t_block *block);


void	*malloc(size_t size)
{
	if (normalize_size(&size) == -1)
		return (NULL);

	return (malloc_internal(size));
}

static void	*malloc_internal(const size_t size)
{
	t_zone_type	type = get_zone_type_by_size(size);
	t_block		*block = get_free_block_for_alloc(type, size);

	if (!block)
		return (NULL);

	block->free = 0;
	split_block(block, size);

	return (get_payload_addr(block));
}


/**
 * @brief Retrieve a free block for the new allocation
 * If there is no free block of the corresponding type,
 * we create a new zone with default block
 * @param type The type of the allocation (TINY, SMALL or LARGE)
 * @param size The aligned size of the allocation
 * @return Block pointer
 */
static t_block	*get_free_block_for_alloc(const t_zone_type type, const size_t size)
{
	t_zone	*zone = NULL;
	t_block	*block = NULL;

	if (type != LARGE)
	{
		block = find_free_block(type, size);
		if (block)
			return (block);
	}
	zone = create_new_zone(type, size);
	if (!zone)
		return (NULL);
	return (zone->blocks);
}

/**
 * @brief Return payload address of a block
 * @param block Pointer to the beginning of the block
 * @return payload address of the block
 */
static void	*get_payload_addr(t_block *block)
{
	return ( (void *) ( (char *) block + BLOCK_HEADER_SIZE ));
}
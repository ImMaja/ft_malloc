#include "alloc_internal.h"

static int		get_free_block_for_alloc(const t_zone_type type, const size_t size, t_zone **out_zone, t_block **out_block);
static void		*get_payload_addr(t_block *block);


void	*malloc_internal(const size_t size)
{
	t_zone_type	type = get_zone_type_by_size(size);
	t_zone		*zone = NULL;
	t_block		*block = NULL;

	if (get_free_block_for_alloc(type, size, &zone, &block) != 0)
		return (NULL);

	block->free = 0;
	zone->used_blocks++;
	split_block(block, size);

	return (get_payload_addr(block));
}


/**
 * @brief Retrieve a free block for the new
 * alloc and corresponding zone. If there is
 * no free block of the corresponding type,
 * we create a new zone with default block.
 * The function set zone and block in *out_zone and *out_block ptrs.
 * If no existing block founded, and creating a new zone also failed,
 * both remains NULL and function return error
 * @param type The type of the allocation (TINY, SMALL or LARGE)
 * @param size The aligned size of the allocation
 * @param out_zone Pointer to zone pointer
 * @param out_block Pointer to block pointer
 * @return 0 in success, -1 otherwise
 */
static int	get_free_block_for_alloc(const t_zone_type type, const size_t size, t_zone **out_zone, t_block **out_block)
{
	if (!out_zone || !out_block)
		return (-1);

	if (type != LARGE)
	{
		if (find_free_block(type, size, out_zone, out_block) == 0)
			return (0);
	}
	*out_zone = create_new_zone(type, size);
	if (!*out_zone)
		return (-1);
	*out_block = (*out_zone)->blocks;
	return (0);
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
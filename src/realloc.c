#include "../include/alloc.h"

static void	*realloc_internal(void *ptr, const size_t size, t_zone *zone, t_block *block);
static void	*shrink_realloc_internal(void *ptr, const size_t size, t_zone *zone, t_block *block, const t_zone_type old_zone_type, const t_zone_type new_zone_type);
static void	*grow_realloc_internal(void *ptr, const size_t size, t_block *block, const t_zone_type old_zone_type, const t_zone_type new_zone_type);
static void	*new_block_realloc(void *ptr, const size_t new_size, const size_t original_size);


void	*realloc(void *ptr, size_t size)
{
	t_zone	*zone = NULL;
	t_block	*block	= NULL;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}

	zone = find_zone_from_payload_ptr(ptr);
	// Not an address from my allocator
	if (!zone)
		return (NULL);

	block = find_block_from_payload_ptr(zone, ptr);
	// Not a valid payload address
	if (!block)
		return (NULL);

	// Block is already freed
	if (block->free)
		return (NULL);

	if (normalize_size(&size) == -1)
		return (NULL);

	// Same size as current block size
	if (size == block->payload_size)
		return (ptr);

	return (realloc_internal(ptr, size, zone, block));
}


static void	*realloc_internal(void *ptr, const size_t size, t_zone *zone, t_block *block)
{
	t_zone_type	old_zone_type = zone->type;
	t_zone_type	new_zone_type = get_zone_type_by_size(size);

	// Shrink reallocation
	if (size < block->payload_size)
	{
		return (shrink_realloc_internal(ptr, size, zone, block, old_zone_type, new_zone_type));
	}
	// Grow reallocation
	return (grow_realloc_internal(ptr, size, block, old_zone_type, new_zone_type));
}


/**
 * @brief Perform a shrink reallocation
 * (new requested payload is smaller then current payload size)
 * For TINY/SMALL reallocation:
 *     Block stay in the same zone
 *     Create a free block with remaining memory if possible
 *     Return same ptr
 * For LARGE reallocation:
 *     LARGE -> LARGE: munmap useless pages of zone if any
 *     LARGE -> TINY/SMALL: reallocate in corresponding zone
 * @param ptr Pointer to current payload
 * @param size New requested and aligned size of the payload
 * @param block Pointer to the block of the payload
 * @param old_zone_type Type of the current allocation
 * @param new_zone_type Type of the new reallocation
 */
static void	*shrink_realloc_internal(void *ptr, const size_t size, t_zone *zone, t_block *block, const t_zone_type old_zone_type, const t_zone_type new_zone_type)
{
	size_t	new_zone_size = 0;

	// Current block is a LARGE allocation
	if (old_zone_type == LARGE)
	{
		// LARGE to LARGE
		if (new_zone_type == LARGE)
		{
			// Calculate new size of the zone
			new_zone_size = calculate_zone_size(LARGE, size);
			if (new_zone_size == 0)
				return (NULL);

			// Realloc does not reduce zone size
			if (new_zone_size == zone->size)
			{
				split_block(block, size);
				return (ptr);
			}

			// Realloc does reduce zone size, try to delete useless pages
			// If somethings fails, fallback to new_block_realloc
			if (reduce_large_zone_size(zone, size, new_zone_size) != 0)
				return (new_block_realloc(ptr, size, size));

			// Successfull shrink of a LARGE -> LARGE
			return (ptr);
		}

		// LARGE to TINY/SMALL
		else
			return (new_block_realloc(ptr, size, size));
	}
	// Current block is a TINY/SMALL allocation

	// If remaining memory is not enough to create a free block
	// Return the same ptr
	if (block->payload_size - size < MIN_BLOCK_SIZE)
		return (ptr);

	// Shrink the block and create a new free block
	// Return the same ptr
	split_block(block, size);
	return (ptr);
}


/**
 * @brief Perform a grow reallocation
 * (new requested payload is bigger then current payload size)
 * Try to extend current block if possible or create a new one
 * @param ptr Pointer to current payload
 * @param size New requested and aligned size of the payload
 * @param block Pointer to the block of the payload
 * @param old_zone_type Type of the current allocation
 * @param new_zone_type Type of the new reallocation
 */
static void	*grow_realloc_internal(void *ptr, const size_t size, t_block *block, const t_zone_type old_zone_type, const t_zone_type new_zone_type)
{
	// New size does not upgrade the allocation type
	if (new_zone_type == old_zone_type)
	{
		// Try an in-place grow
		// Return same ptr if success
		if (inplace_grow(block, size) == 0)
			return (ptr);
	}

	// New size does upgrade the allocation type
	// or grow in-place failed
	// Return new ptr
	return (new_block_realloc(ptr, size, block->payload_size));
}


/**
 * @brief Use malloc to allocate a new block,
 * then copy using ft_memcpy from previous ptr to new ptr
 * and free previous block
 * @param ptr Original payload pointer
 * @param new_size Aligned size of the reallocation
 * @param copy_size The copy size
 * @return In case of malloc failure, return NULL and does not deallocate block
 * Return new pointer otherwise
 */
static void	*new_block_realloc(void *ptr, const size_t new_size, const size_t copy_size)
{
	void	*new_ptr = malloc(new_size);

	if (!new_ptr)
		return (NULL);

	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}

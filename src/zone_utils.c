#include <stdint.h>

#include "../include/alloc.h"


/**
 * @brief Retrieve an allocation type by its size
 * @param size The aligned size of the allocation
 * @return The corresponding type (TINY, SMALL or LARGE)
 */
t_zone_type	get_zone_type_by_size(const size_t size)
{
	if (size > SMALL_BLOCK_SIZE)
		return (LARGE);
	else if (size > TINY_BLOCK_SIZE && size <= SMALL_BLOCK_SIZE)
		return (SMALL);
	return (TINY);
}


/**
 * @brief Push the 'new_zone' in the zones linked-list of the alloc struct
 * @param new_zone The new zone to push
 */
void	push_zone(t_zone *new_zone)
{
	t_zone	**zones = get_zones();
	t_zone	*last;

	if (!new_zone)
		return ;

	if (*zones == NULL)
	{
		*zones = new_zone;
		new_zone->prev = NULL;
		new_zone->next = NULL;
		return ;
	}

	last = *zones;
	while (last->next)
		last = last->next;

	last->next = new_zone;
	new_zone->prev = last;
}


/**
 * @brief Remove a zone element from the zones linked-list
 * @param prev The previous element from unlink
 * @param next The next element from unlink
 */
void	unlink_zone(t_zone *prev, t_zone *next)
{
	t_zone **zones = get_zones();

	if (prev)
		prev->next = next;
	else
		*zones = next;

	if (next)
		next->prev = prev;
}


/**
 * @brief Calculate the size for a new zone (mmap allocation)
 * The size is aligned on page multiple
 * @param type The type (TINY, SMALL or LARGE) of the new zone
 * @param size The aligned size for LARGE allocation
 * @return mmap size
 */
size_t	calculate_zone_size(const t_zone_type type, const size_t size)
{
	size_t	raw_size;

	if (type == TINY)
		raw_size = ZONE_HEADER_SIZE
			+ (BLOCK_HEADER_SIZE * ZONE_ALLOC_COUNT)
			+ (TINY_BLOCK_SIZE * ZONE_ALLOC_COUNT);
	else if (type == SMALL)
		raw_size = ZONE_HEADER_SIZE 
			+ (BLOCK_HEADER_SIZE * ZONE_ALLOC_COUNT)
			+ (SMALL_BLOCK_SIZE * ZONE_ALLOC_COUNT);
	else
	{
		// Check overflow
		if (size > SIZE_MAX - ZONE_HEADER_SIZE - BLOCK_HEADER_SIZE)
			return (0);
		raw_size = ZONE_HEADER_SIZE
			+ BLOCK_HEADER_SIZE
			+ size;

	}

	return (align_page(raw_size));
}


/**
 * @brief Search in wich zone the ptr is
 * @param ptr Pointer to a payload
 * @return Corresponding zone pointer if found
 * NULL otherwise
 */
t_zone	*find_zone_from_payload_ptr(const void *ptr)
{
	const uintptr_t	payload_addr = (uintptr_t) ptr;
	t_zone	*z = *get_zones();
	uintptr_t		z_end_addr = 0;

	// Iterate zones linked-list, check if the
	// payload_addr is in the range of a zone
	while (z)
	{
		z_end_addr = (uintptr_t) ( (char *) z + z->size );
		if (payload_addr > (uintptr_t) z && payload_addr < z_end_addr)
			return (z);
		z = z->next;
	}
	return (NULL);
}


/**
 * @brief Find an empty zone (used_blocks == 0) of type 'type'
 * The function will exclude the 'exclude' zone from the search
 * @param type The zone type for the search
 * @param exclude One zone to exclude from the search
 * @return Pointer to the first empty zone (different from exclude) founded
 * NULL if no zone founded
 */
t_zone	*find_empty_zone(const t_zone_type type, const t_zone *exclude)
{
	t_zone	*iter = *get_zones();

	while (iter)
	{
		if (iter->type == type && iter->used_blocks == 0 && iter != exclude)
			return (iter);
		iter = iter->next;
	}

	return (NULL);
}

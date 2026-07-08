#include "../include/alloc.h"

static size_t	align_page(const size_t size);


/**
 * @brief Retrieve an allocation type by its size
 * @param size The aligned size of the allocation
 * @return The corresponding type (TINY, SMALL or LARGE)
 */
t_zone_type	get_zone_type_by_size(const size_t size)
{
	if (size > SMALL_BLOCK_SIZE)
		return (LARGE);
	else if (size > TINY_BLOCK_SIZE && size < SMALL_BLOCK_SIZE)
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
 * @brief Calculate the length for a new zone (mmap allocation)
 * The length is aligned on page multiple
 * @param type The type (TINY, SMALL or LARGE) of the new zone
 * @param size The aligned size for LARGE allocation
 * @return mmap length
 */
size_t	calculate_zone_length(const t_zone_type type, const size_t size)
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
		raw_size = ZONE_HEADER_SIZE
			+ BLOCK_HEADER_SIZE
			+ size;

	return (align_page(raw_size));
}


/**
 * @brief Align the zone size on a page multiple (most of the time 4096)
 * ex: size = 16048, return 16384
 * @param size The raw size of a zone
 * @return Aligned size
 */
static size_t	align_page(const size_t size)
{
	size_t	page_size = get_page_size();
	size_t	rem;

	if (page_size == 0)
		return (0);
	
	rem = size % page_size;
	if (rem == 0)
		return (size);
	return ( size + (page_size - rem) );
}

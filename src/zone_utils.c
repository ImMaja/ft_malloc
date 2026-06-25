#include "../include/alloc.h"

#include <unistd.h>


/**
 * @brief Iterate on a linked-list of zone
 * Can be a linked-list of either TINY, SMALL or LARGE zones
 * @param heap_zone Linked-list of zones
 * @param new_zone New node to insert in heap_zone
 */
void	push_new_zone_in_linked_list(t_zone **heap_zone, t_zone *new_zone)
{
	t_zone	*iter;
	// Should nerver happend
	if (!heap_zone)
		return ;
	
	if (!*heap_zone)
	{
		*heap_zone = new_zone;
		return ;
	}

	iter = *heap_zone;
	while (iter->next)
		iter = iter->next;

	new_zone->prev = iter;
	iter->next =new_zone;
}


/**
 * @brief Align the zone size on a page multiple (most of the time 4096)
 * ex: size = 16048, return 16384
 * @param size The raw size of a zone
 * @return Aligned size
 */
static size_t	align_page(const size_t size)
{
	long	page_size = sysconf(_SC_PAGESIZE);
	size_t	rem;

	// Check for errors
	if (page_size <= 0)
		return (0);
	
	rem = size % (size_t) page_size;
	if (rem == 0)
		return (size);
	return ( size + ((size_t) page_size - rem) );
}


/**
 * @brief Calculate the length for a new zone (mmap allocation)
 * The length is aligned on page multiple
 * @param type The type (TINY, SMALL or LARGE) of the new heap zone
 * @param size The size parameter of malloc (used only for LARGE)
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
			+ ALIGN_UP(size);

	return (align_page(raw_size));
}


/**
 * @brief Initialize zone headers with default value
 * @param mem The new zone
 * @param type Type of the zone (TINY, SMALL or LARGE)
 * @param size The full length of the zone
 */
void	init_zone_header(t_zone *mem, const t_zone_type type, const size_t size)
{
	mem->type = type;
	mem->size = size;
	mem->blocks = NULL;
	mem->next = NULL;
	mem->prev = NULL;
}

#include <stdint.h>

#include "../include/alloc.h"


/**
 * @brief Find the corresponding zone of a payload ptr
 * If ptr is not in any zone, this functionn will return NULL
 * @param ptr Pointer to a payload
 */
t_zone	*find_zone_from_payload_ptr(const void *ptr)
{
	const uintptr_t	payload_addr = (uintptr_t) ptr;
	const t_heap	*heap = get_heap();
	const t_zone	*zones[HEAP_ELEM] = {
		heap->tiny,
		heap->small,
		heap->large
	};
	t_zone			*z = NULL;
	uintptr_t		z_end_addr = 0;

	// Iterate on all heap elements, check if the
	// payload_addr is in the range of a zone
	for (uint8_t i = 0 ; i < HEAP_ELEM ; i++)
	{
		z = zones[i];
		while (z)
		{
			z_end_addr = (uintptr_t) ((char *) z + z->size);
			if (payload_addr > (uintptr_t) z && payload_addr <= z_end_addr)
				return (z);
			z = z->next;
		}
	}
	return (NULL);
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
	t_block	*to_find = NULL;
	t_block	*b = NULL;

	if (!zone)
		return (NULL);

	// Retrieve a ptr to the beginning of the block
	to_find = (t_block *) ( (char *) zone - BLOCK_HEADER_SIZE );

	// Check if the address is still in the zone
	if ( (uintptr_t) to_find < (uintptr_t) zone )
		return (NULL);

	// Iterate on all blocks of the zone
	b = zone->blocks;
	while (b)
	{
		if ( (uintptr_t) b == (uintptr_t) to_find )
			return (to_find);
		b = b->next;
	}

	return (NULL);
}

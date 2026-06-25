#include <unistd.h>

#include "../include/alloc.h"

/**
 * @brief
 */
void	create_default_block(t_zone *zone)
{
	t_block	*b = (t_block *) zone + ZONE_HEADER_SIZE;

	zone->blocks = b;
	b->payload_size = zone->size - ZONE_HEADER_SIZE - BLOCK_HEADER_SIZE;
	b->free = 0;
	b->next = NULL;
	b->prev = NULL;
}

/**
 * @brief
 */
// void	*create_block(t_zone *zone, const size_t size)
// {
	// return ();
// }

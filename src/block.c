#include <unistd.h>

#include "../include/alloc.h"

/**
 * @brief Create a default block in a new zone
 * Default blok will use all memory available in the zone
 * @param zone The zone who need a default block
 */
void	create_default_block(t_zone *zone)
{
	t_block	*b = (t_block *) ( (char *) zone + ZONE_HEADER_SIZE );

	zone->blocks = b;
	b->payload_size = zone->size - ZONE_HEADER_SIZE - BLOCK_HEADER_SIZE;
	b->free = 1;
	b->next = NULL;
	b->prev = NULL;
}

t_block	*find_available_block(const t_zone *zone, const size_t size)
{
	t_block	*b = NULL;

	while (zone)
	{
		b = zone->blocks;
		while (b)
		{
			if (b->free && b->payload_size >= size + BLOCK_HEADER_SIZE + MIN_PAYLOAD_SIZE)
				return (b);
			b = b->next;
		}
		zone = zone->next;
	}

	return (NULL);
}

/**
 * @brief Split an available block into a newly allocated block
 * We assume that 'split_block' is available and have enough
 * room for the new alloc of size 'size'
 * @param split The block to split
 * @param size The size of the new block (already aligned)
 * @return Pointer to the ew block payload
 */
void	*split_block(t_block *split, const size_t size)
{
	t_block	*next = (t_block *) ( (char *) split + BLOCK_HEADER_SIZE + size );

	split->next = next;
	next->prev = split;

	next->payload_size = split->payload_size - BLOCK_HEADER_SIZE - size;
	next->free = 1;
	next->next = NULL;

	split->payload_size = size;
	split->free = 0;
	split->payload_size = size;

	return ( (char *) split + BLOCK_HEADER_SIZE);
}

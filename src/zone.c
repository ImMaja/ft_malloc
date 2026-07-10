#include <unistd.h>
#include <sys/mman.h>

#include "../include/alloc.h"

/**
 * @brief Allocate a new zone with mmap and push it in zones linked-list
 * @param type Zine type, TINY, SMALL or LARGE
 * @param size Aligned payload size
 * @return ptr to the new zone on success, NULL on error
 */
t_zone	*create_new_zone(const t_zone_type type, const size_t size)
{
	size_t	zone_length;
	t_zone	*mem;

	zone_length = calculate_zone_size(type, size);
	if (zone_length == 0)
		return (NULL);

	mem = (t_zone *) mmap(NULL, zone_length, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	// Return error if mmap allocation failed
	if (mem == MAP_FAILED)
		return (NULL);

	// Initialize new zone header
	mem->type = type;
	mem->size = zone_length;
	mem->used_blocks = 0;
	mem->blocks = NULL;
	mem->next = NULL;
	mem->prev = NULL;

	// Initialize a default block for the new zone
	// Creating a default block should not fail, but in case it did,
	// we simply munmap the zone and return NULL
	if (create_default_block(mem) != 0)
	{
		munmap((void *) mem, zone_length);
		return (NULL);
	}

	// Push the new zone in zones linked-list
	push_zone(mem);

	return (mem);
}


/**
 * @brief Reduce the size of a large zone. Shrinked memory is munmaped
 * @param zone The LARGE zone to shrink
 * @param new_zone_size The new size for the zone
 * @return 0 on success, != 0 on error
 */
int	reduce_large_zone_size(t_zone *zone, const size_t realloc_size, const size_t new_zone_size)
{
	void	*cut = NULL;
	size_t	munmap_size = 0;
	size_t	remaining = 0;
	int		munmap_ret = -1;
	t_block	*free_block = NULL;

	// Should not happen i guess
	if (!zone || zone->type != LARGE || !zone->blocks)
		return (-1);
	if (new_zone_size >= zone->size)
		return (-1);
	if (new_zone_size < ZONE_HEADER_SIZE + BLOCK_HEADER_SIZE + realloc_size)
		return (-1);

	cut = (void *) ( (char *) zone + new_zone_size );
	munmap_size = zone->size - new_zone_size;
	remaining = new_zone_size - ZONE_HEADER_SIZE - BLOCK_HEADER_SIZE - realloc_size;

	// Munmap useless pages
	munmap_ret = munmap(cut, munmap_size);
	if (munmap_ret != 0)
		return (munmap_ret);

	// At this point, munmap was successfull

	// Shrink block to the new realloc size
	zone->blocks->payload_size = realloc_size;

	zone->size = new_zone_size;

	// Enough remaining memory for a free block
	if (remaining >= MIN_BLOCK_SIZE)
	{
		free_block = (t_block *) ( (char *) zone + ZONE_HEADER_SIZE + BLOCK_HEADER_SIZE + zone->blocks->payload_size );
		free_block->free = 1;
		free_block->payload_size = remaining - BLOCK_HEADER_SIZE;
		free_block->next = NULL;
		free_block->prev = zone->blocks;

		zone->blocks->next = free_block;
	}
	// Not enough remaining memory for a free block
	else
	{
		zone->blocks->next = NULL;
		zone->blocks->payload_size = zone->size - ZONE_HEADER_SIZE - BLOCK_HEADER_SIZE;
	}

	return (0);
}


/**
 * @brief Delete a zone. Munmap and unlink zone
 * If somethings goes wrong, zone is not deleted and not unlinked
 * @param zone The zone to remove
 * @return 0 on success, != 0 on failure
 */
int	delete_zone(t_zone *zone)
{
	int		munmap_ret = -1;
	t_zone	*prev = NULL;
	t_zone	*next = NULL;

	if (!zone)
		return (-1);

	prev = zone->prev;
	next = zone->next;

	// Munmap zone, return immediatly in case of failure
	munmap_ret = munmap(zone, zone->size);
	if (munmap_ret != 0)
		return (munmap_ret);

	unlink_zone(prev, next);
	return (0);
}

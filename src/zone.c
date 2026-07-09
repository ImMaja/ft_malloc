#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>

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
	mem->blocks = NULL;
	mem->next = NULL;
	mem->prev = NULL;

	// Initialize a default block for the new zone
	// Creating a default block should not fail, but in case it did,
	// we simply munmap the zone and return NULL
	if (create_default_block(mem) == 1)
	{
		munmap((void *) mem, zone_length);
		return (NULL);
	}

	// Push the new zone in zones linked-list
	push_zone(mem);

	return (mem);
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

	// If this fail, we are so fucked
	if (!zone || zone->type != LARGE || !zone->blocks)
		return (1);
	if (new_zone_size >= zone->size)
		return (1);
	if (new_zone_size < ZONE_HEADER_SIZE + BLOCK_HEADER_SIZE + realloc_size)
		return (1);

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

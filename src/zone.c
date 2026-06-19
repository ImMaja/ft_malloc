#include "../include/alloc.h"

#include <stdbool.h>
#include <unistd.h>
#include <sys/mman.h>

/**
 * @brief If a t_zone_type is not TINY, SMALL or LARGE, the type is invalid
 * @param type The enum to check
 * @return true if valid, false otherwise
 */
static bool	check_type(const t_zone_type type)
{
	if (type != TINY && type != SMALL && type != LARGE)
		return (false);
	return (true);
}

/**
 * @brief Iterate on a linked-list of zone
 * Can be a linked-list of either TINY, SMALL or LARGE zones
 * @param heap_zone Linked-list of zones
 * @param new_zone New node to insert in heap_zone
 */
static void	push_new_zone(t_zone **heap_zone, t_zone *new_zone)
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
 * @brief Calculate the 'length' for the mmap allocation
 * @param type The type (TINY, SMALL or LARGE) of the new heap zone
 * @param size The size parameter of malloc (used only for LARGE)
 * @return mmap length
 */
static size_t	calculate_zone_length(const t_zone_type type, const size_t size)
{
	if (type == TINY)
		return ( ZONE_HEADER_SIZE + (BLOCK_HEADER_SIZE * ZONE_ALLOC_COUNT) + (TINY_BLOCK_SIZE * ZONE_ALLOC_COUNT) );
	else if (type == SMALL)
		return ( ZONE_HEADER_SIZE + (BLOCK_HEADER_SIZE * ZONE_ALLOC_COUNT) + (SMALL_BLOCK_SIZE * ZONE_ALLOC_COUNT) );
	return (ZONE_HEADER_SIZE + BLOCK_HEADER_SIZE + ALIGN_UP(size));
}


/**
 * @brief Allocate a new zone with mmap and add it in corresponding heap linked-list
 * @param type TINY, SMALL or LARGE -> Zone type
 * @param size The size of the zone to allocate
 * @return 0 on success, -1 otherwise
 */
int	create_new_zone(const t_zone_type type, const size_t size)
{
	t_zone	**heap_zone;
	size_t	zone_length;
	void	*mem;

	// Should never happend
	if (!check_type(type))
	{
		write(2, "[ERROR] 'type' in 'create_new_zone' is NULL\n", 44);
		return (-1);
	}

	heap_zone = get_zone_ptr_by_type(type);
	zone_length = calculate_zone_length(type, size);
	write(1, "[INFO] Calling mmap with length: ", 33);
	ft_putnbr_fd(zone_length, 1);
	write(1, " bytes\n", 7);
	mem = mmap(NULL, zone_length, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	// Return error if mmap allocation failed
	if (mem == MAP_FAILED)
		return (-1);

	((t_zone *)mem)->type = type;
	((t_zone *)mem)->size = zone_length;
	((t_zone *)mem)->blocks = NULL;
	((t_zone *)mem)->next = NULL;
	((t_zone *)mem)->prev = NULL;

	// Push the new zone in corresponding linked-list
	push_new_zone(heap_zone, (t_zone *) mem);

	return (0);
}


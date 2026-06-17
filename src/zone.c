#include "../include/alloc.h"

#include <unistd.h>
#include <sys/mman.h>

/**
 * @brief Iterate on a linked-list of zone
 * Can be a linked-list of either TINY, SMALL or LARGE zones
 * @param zone_lst Linked-list of zones
 * @param new_zone New node to insert in zone_lst
 */
static void	push_new_zone(t_zone **zone_lst, t_zone *new_zone)
{
	t_zone	*iter;

	// Should nerver happend
	if (!zone_lst)
		return ;

	if (!*zone_lst)
	{
		*zone_lst = new_zone;
		return ;
	}

	iter = *zone_lst;
	while (iter)
		iter = iter->next;

	new_zone->prev = iter;
	iter->next =new_zone;
}


/**
 * @brief Allocate a new zone with mmap and add it in corresponding heap linked-list
 * @param type TINY, SMALL or LARGE -> Zone type
 * @param size The size of the zone to allocate
 * @return 0 on success, -1 otherwise
 */
int	create_new_zone(const t_zone_type type, const size_t size)
{
	t_zone	*zone_lst = get_zone_ptr_by_type(type);
	void	*mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	// Return error if mmap allocation failed
	if (mem == MAP_FAILED)
		return (-1);

	push_new_zone(&zone_lst, (t_zone *) mem);

	return (0);
}


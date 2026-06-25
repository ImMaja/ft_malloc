#include <unistd.h>
#include <sys/mman.h>

#include "../include/alloc.h"

/**
 * @brief Allocate a new zone with mmap and add it in corresponding heap linked-list
 * @param type TINY, SMALL or LARGE -> Zone type
 * @param size The size of the requested block payload
 * @return ptr to the new zone on success, NULL on error
 */
t_zone	*create_new_zone(const t_zone_type type, const size_t size)
{
	t_zone	**heap_zone = get_zone_ptr_by_type(type);
	size_t	zone_length;
	void	*mem;

	// Should never happend
	if (!heap_zone)
	{
		write(2, "[ERROR] 'type' in 'create_new_zone' is invalid\n", 44);
		return (NULL);
	}

	zone_length = calculate_zone_length(type, size);
	if (zone_length == 0)
		return (NULL);

	write(1, "[INFO] Calling mmap with length: ", 33);
	ft_putnbr_fd(zone_length, 1);
	write(1, " bytes\n", 7);

	mem = mmap(NULL, zone_length, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	// Return error if mmap allocation failed
	if (mem == MAP_FAILED)
		return (NULL);

	// Initialize new zone header
	init_zone_header((t_zone *) mem, type, zone_length);

	// Initialize a default block for the new zone
	create_default_block((t_zone *) mem);

	// Push the new zone in corresponding linked-list
	push_new_zone_in_linked_list(heap_zone, (t_zone *) mem);

	return ((t_zone *) mem);
}


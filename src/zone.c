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

	zone_length = calculate_zone_length(type, size);
	if (zone_length == 0)
		return (NULL);

	mem = mmap(NULL, zone_length, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

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
	create_default_block(mem, size);

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

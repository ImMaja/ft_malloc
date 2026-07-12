#include <stdint.h>

#include "alloc_internal.h"

/**
 * @brief Align size on 16 bytes using ALIGN_UP macro
 * Set a minimal size to MIN_PAYLOAD_SIZE if size == 0
 * Check for overflow when aligning
 * @param size Pointer to the size_t variable to align
 * @return -1 on invalid size, 0 otherwise
 */
int	normalize_size(size_t *size)
{
	if (!size)
		return (-1);

	if (size == 0)
		*size = MIN_PAYLOAD_SIZE;

	if (*size > SIZE_MAX - (ALIGNMENT - 1))
		return (-1);

	*size = ALIGN_UP(*size);
	return (0);
}


/**
 * @brief Align the zone size on a page multiple (most of the time 4096)
 * ex: size = 16048, return 16384
 * @param size The raw size of a zone
 * @return Aligned size
 */
size_t	align_page(const size_t size)
{
	size_t	page_size = get_page_size();
	size_t	rem;

	if (page_size == 0)
		return (0);
	
	rem = size % page_size;
	if (rem == 0)
		return (size);

	// Check overflow
	if (size > SIZE_MAX - (page_size - rem))
		return (0);

	return ( size + (page_size - rem) );
}

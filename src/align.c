#include <stdint.h>

#include "../include/alloc.h"

/**
 * @brief Align size on 16 bytes using ALIGN_UP macro
 * Also check for overflow
 * @param size Pointer to the size_t variable to align
 * @return -1 on invalid size, 0 otherwise
 */
int	normalize_size(size_t *size)
{
	if (!size || *size == 0)
		return (-1);
	if (*size > SIZE_MAX - (ALIGNMENT - 1))
		return (-1);

	*size = ALIGN_UP(*size);
	return (0);
}

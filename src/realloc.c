#include "../include/alloc.h"

void	*realloc(void *ptr, size_t size)
{
	t_zone	*z = NULL;
	t_block	*b	= NULL;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}

	z = find_zone_from_payload_ptr(ptr);
	// Not an address from my allocator, wtf bro?
	if (!z)
		return (NULL);

	b = find_block_from_payload_ptr(z, ptr);
	// Not a valid payload address, again wtf?
	if (!b)
		return (NULL);

	// Block is already freed
	if (b->free)
		return (NULL);

	size = ALIGN_UP(size);

	// Same size as current block size
	if (size == b->payload_size)
		return (ptr);


	// Shrink cases,
	// new size is smaller then current payload_size
	if (size < b->payload_size)
	{
		// Difference is not enought for a free block, no changes
		if (b->payload_size - size < MIN_SPLIT_SIZE)
			return (ptr);

		// checker si on retrograde le type
		// si oui, malloc, memcpy et free
		// puis retourner l'adresse retourne par malloc ici
		// return (...);

		// sinon on split
		// donc cree un block libre
		// checker si le prochain block est aussi libre, si oui les fussioners
		// puis retourner le meme ptr ici
		return (ptr);
	}

	// Grow cases
	// New size is bigger then current payload_size

	// If new size upgrade the allocation type
	if (b->payload_size <= TINY && size > TINY
		|| b->payload_size <= SMALL && size > SMALL)
	{
		// upgrade le type
		// on fait juste un malloc, memcpy et free du ptr

	}

	// On n'upgrade pas le type, on check si on peux
	// agrandir le block actuel, sinon malloc, memcpy et free du ptr

	return (NULL);
}

#include <unistd.h>

#include "../include/alloc.h"
#include "../libft/libft.h"

/**
 * 
 */
void	*malloc(size_t size)
{
	// Check if size is LARGE type
	if (size >= SMALL_BLOCK_SIZE)
	{
		ft_printf("Large malloc called\n\n");
	}

	return (NULL);
}

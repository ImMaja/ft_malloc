#include <unistd.h>

#include "../ft_printf/ft_printf.h"
#include "../include/alloc.h"

/**
 * 
 */
void	*malloc(size_t size)
{
	ft_printf("malloc called -------------------------\n");
	// Check if size is LARGE type
	if (size >= SMALL_BLOCK_SIZE)
	{
		int	ret = create_new_zone(LARGE, size);
		ft_printf("malloc is a LARGE allocation ----------\n");
		ft_printf("create_new_zone() returned: %d\n", ret);
	}

	return (NULL);
}

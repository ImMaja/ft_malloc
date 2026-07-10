#include "../../include/alloc.h"

void	*calloc(size_t nmemb, size_t size)
{
	size_t	total = 0;
	void	*ptr = NULL;

	// Check overflow
	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);

	total = nmemb * size;

	ptr = malloc(total);
	if (!ptr)
		return (NULL);

	ft_memset(ptr, 0, total);
	return (ptr);
}

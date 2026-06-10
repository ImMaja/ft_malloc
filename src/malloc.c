#include <unistd.h>

void	*malloc(size_t size)
{
	(void) size;
	write(1, "Salut\n\n", 7);

	return (NULL);
}

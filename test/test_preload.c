#include <dlfcn.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int	fail(const char *message, size_t length)
{
	write(STDERR_FILENO, "preload test: ", 14);
	write(STDERR_FILENO, message, length);
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

int	main(void)
{
	unsigned char	*small;
	unsigned char	*large;
	unsigned char	*zeroed;
	size_t			i;

	if (!dlsym(RTLD_DEFAULT, "show_alloc_mem"))
		return (fail("libft_malloc.so is not preloaded",
				sizeof("libft_malloc.so is not preloaded") - 1));
	small = malloc(37);
	large = malloc(4096);
	zeroed = calloc(73, 9);
	if (!small || !large || !zeroed)
		return (fail("allocation failed", sizeof("allocation failed") - 1));
	memset(small, 0x2a, 37);
	memset(large, 0x5a, 4096);
	i = 0;
	while (i < 73 * 9)
	{
		if (zeroed[i] != 0)
			return (fail("calloc did not return zeroed memory",
					sizeof("calloc did not return zeroed memory") - 1));
		i++;
	}
	small = realloc(small, 700);
	if (!small)
		return (fail("realloc failed", sizeof("realloc failed") - 1));
	i = 0;
	while (i < 37)
	{
		if (small[i] != 0x2a)
			return (fail("realloc lost data",
					sizeof("realloc lost data") - 1));
		i++;
	}
	free(small);
	free(large);
	free(zeroed);
	write(STDOUT_FILENO, "LD_PRELOAD test passed.\n",
		sizeof("LD_PRELOAD test passed.\n") - 1);
	return (0);
}

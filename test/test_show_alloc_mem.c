#include "ft_malloc.h"

#include <stdlib.h>
#include <unistd.h>

static void	print_title(const char *title, size_t length)
{
	write(STDOUT_FILENO, "\n=== ", 5);
	write(STDOUT_FILENO, title, length);
	write(STDOUT_FILENO, " ===\n", 5);
}

int	main(void)
{
	void	*a;
	void	*b;
	void	*c;
	void	*d;

	print_title("empty allocator", sizeof("empty allocator") - 1);
	show_alloc_mem();
	a = malloc(32);
	b = malloc(420);
	c = malloc(2401);
	if (!a || !b || !c)
		return (1);
	print_title("one TINY, one SMALL, one LARGE",
		sizeof("one TINY, one SMALL, one LARGE") - 1);
	show_alloc_mem();
	b = realloc(b, 64);
	c = realloc(c, 128);
	if (!b || !c)
		return (1);
	print_title("after shrinking both allocations",
		sizeof("after shrinking both allocations") - 1);
	show_alloc_mem();
	free(a);
	free(b);
	free(c);
	a = malloc(64);
	b = malloc(64);
	c = malloc(64);
	if (!a || !b || !c)
		return (1);
	free(a);
	free(b);
	print_title("two adjacent blocks freed",
		sizeof("two adjacent blocks freed") - 1);
	show_alloc_mem();
	d = malloc(128);
	if (!d)
		return (1);
	print_title("merged space reused after a 128-byte request",
		sizeof("merged space reused after a 128-byte request") - 1);
	show_alloc_mem();
	free(c);
	free(d);
	print_title("after every free", sizeof("after every free") - 1);
	show_alloc_mem();
	return (0);
}

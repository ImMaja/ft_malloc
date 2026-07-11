#include <stdint.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdlib.h>

#include "include/ft_malloc.h"

typedef void	(*t_show_alloc_mem)(void);

static void	show_allocations(void)
{
	t_show_alloc_mem	show;

	show = (t_show_alloc_mem)dlsym(RTLD_DEFAULT, "show_alloc_mem");
	if (!show)
	{
		write(STDOUT_FILENO, "libft_malloc is not loaded\n", 27);
		return ;
	}
	show();
}


int	main(void)
{
	void	*ptr_1 = malloc(42);
	void	*ptr_2 = malloc(420);
	void	*ptr_3 = malloc(4200);

	write(1, "\n\n", 2);
	show_allocations();


	void	*arr[200] = {};

	for (uint16_t i = 0 ; i < 200 ; i++)
		arr[i] = malloc(512);

	write(1, "\n\n", 2);
	show_allocations();

	for (uint16_t i = 0 ; i < 200 ; i++)
		free(arr[i]);
	free(ptr_1);
	free(ptr_2);

	write(1, "\n\n", 2);
	show_allocations();

	
	ptr_3 = realloc(ptr_3, 800);
	write(1, "\n\n", 2);
	show_allocations();


	ptr_3 = realloc(ptr_3, 40);
	write(1, "\n\n", 2);
	show_allocations();


	free(ptr_3);
	write(1, "\n\n", 2);
	show_allocations();

	return (0);
}

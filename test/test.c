#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../include/alloc.h"

int	main(void)
{
	write(1, "\n\n", 2);

	// void *ptr_1 = malloc(32);
	// void *ptr_2 = malloc(64);
	// void *ptr_3 = malloc(420);
	// void *ptr_4 = malloc(2401);


	// show_alloc_mem();
	// write(1, "\n\n", 2);

	// free(ptr_1);
	// ptr_3 = realloc(ptr_3, 64);
	// ptr_4 = realloc(ptr_4, 128);

	// show_alloc_mem();
	// write(1, "\n\n", 2);

	// free(ptr_2);
	// free(ptr_3);
	// free(ptr_4);


	show_alloc_mem();
	write(1, "\n\n", 2);


	void	*arr[200] = {};

	for (uint32_t i = 0; i < 200; i++)
		arr[i] = malloc(64);

	(void) arr;

	show_alloc_mem();
	write(1, "\n\n", 2);



	return (0);
}






// typedef struct s_test_1
// {
// 	char	a;
// 	char	*b;
// }	t_test_1;


// typedef struct __attribute__((packed)) s_test_2
// {
// 	char	a;
// 	char	*b;
// }	t_test_2;

// int	main(void)
// {
// 	t_test_1	t1 = { '1', strdup("Salut 1") };
// 	t_test_2	t2 = { '2', strdup("Salut 2") };

// 	printf("sizeof(t_test_1): %ld\n", sizeof(t_test_1));
// 	printf("sizeof(t_test_2): %ld\n", sizeof(t_test_2));
// 	printf("\n");

// 	printf("%s\n", t1.b);
// 	printf("%s\n", t2.b);

// 	free(t1.b);
// 	free(t2.b);

// 	return (0);
// }

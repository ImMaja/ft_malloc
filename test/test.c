#include <stdlib.h>

#include <stdio.h>
#include <string.h>

#include "../ft_printf/ft_printf.h"
#include "../include/alloc.h"

int	main(void)
{
	void	*arr[5] = {
		ft_malloc(12),
		ft_malloc(1024),
		ft_malloc(1025),
		ft_malloc(1),
		ft_malloc(244)
	};
	(void) arr;


	ft_printf("\n\n");
	show_alloc_mem();


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

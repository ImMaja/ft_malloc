#ifndef TEST_H
# define TEST_H

# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# include "ft_malloc.h"

# define TEST_ASSERT(condition) \
	do \
	{ \
		if (!(condition)) \
			return (test_failure(#condition, __FILE__, __LINE__)); \
	} while (0)

void	test_putstr(const char *str);
int		test_failure(const char *condition, const char *file, int line);
int		test_memory_is(const void *ptr, size_t size, unsigned char value);
void	test_fill(void *ptr, size_t size, unsigned char value);
size_t	test_max_size(void);

int		test_malloc_boundaries(void);
int		test_malloc_independence(void);
int		test_malloc_many(void);
int		test_malloc_invalid_sizes(void);
int		test_calloc_zeroed(void);
int		test_calloc_overflow(void);
int		test_free_null(void);
int		test_free_reuse(void);
int		test_free_coalescing(void);
int		test_free_orders(void);
int		test_realloc_special_cases(void);
int		test_realloc_shrink(void);
int		test_realloc_grow_in_place(void);
int		test_realloc_grow_with_move(void);
int		test_realloc_zone_transitions(void);
int		test_realloc_large_shrink(void);
int		test_realloc_failure(void);
int		test_stress(void);
int		test_thread_safety(void);

#endif

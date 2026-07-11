#include "test.h"

typedef int	(*t_test_fn)(void);

typedef struct s_test_case
{
	const char	*name;
	t_test_fn	function;
} t_test_case;

static int	run_test(const t_test_case *test)
{
	test_putstr("[TEST] ");
	test_putstr(test->name);
	test_putstr(" ... ");
	if (test->function() != 0)
		return (1);
	test_putstr("OK\n");
	return (0);
}

int	main(void)
{
	const t_test_case	tests[] = {
		{"malloc: boundaries and alignment", test_malloc_boundaries},
		{"malloc: independent blocks", test_malloc_independence},
		{"malloc: many allocations", test_malloc_many},
		{"malloc: invalid sizes", test_malloc_invalid_sizes},
		{"calloc: zeroed memory", test_calloc_zeroed},
		{"calloc: overflow", test_calloc_overflow},
		{"free: NULL", test_free_null},
		{"free: reuse", test_free_reuse},
		{"free: adjacent block coalescing", test_free_coalescing},
		{"free: different orders", test_free_orders},
		{"realloc: special cases", test_realloc_special_cases},
		{"realloc: shrinking", test_realloc_shrink},
		{"realloc: in-place growth", test_realloc_grow_in_place},
		{"realloc: moved growth", test_realloc_grow_with_move},
		{"realloc: zone transitions", test_realloc_zone_transitions},
		{"realloc: large shrinking", test_realloc_large_shrink},
		{"realloc: failure keeps original", test_realloc_failure},
		{"stress: deterministic mixed operations", test_stress},
		{"thread safety: concurrent mixed operations", test_thread_safety},
	};
	const size_t		test_count = sizeof(tests) / sizeof(tests[0]);
	size_t			i;

	test_putstr("Allocator test suite\n");
	i = 0;
	while (i < test_count)
	{
		if (run_test(&tests[i]) != 0)
		{
			test_putstr("Test suite stopped after first failure.\n");
			return (1);
		}
		i++;
	}
	test_putstr("All tests passed.\n");
	return (0);
}

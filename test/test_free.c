#include "test.h"

int	test_free_null(void)
{
	free(NULL);
	return (0);
}

int	test_free_reuse(void)
{
	void		*a;
	void		*b;
	void		*c;
	void		*reused;
	uintptr_t	b_address;

	a = malloc(64);
	b = malloc(64);
	c = malloc(64);
	TEST_ASSERT(a != NULL && b != NULL && c != NULL);
	b_address = (uintptr_t)b;
	free(b);
	reused = malloc(64);
	TEST_ASSERT(reused != NULL);
	TEST_ASSERT((uintptr_t)reused == b_address);
	free(a);
	free(reused);
	free(c);
	return (0);
}

int	test_free_coalescing(void)
{
	void		*a;
	void		*b;
	void		*c;
	void		*merged;
	uintptr_t	a_address;

	a = malloc(64);
	b = malloc(64);
	c = malloc(64);
	TEST_ASSERT(a != NULL && b != NULL && c != NULL);
	a_address = (uintptr_t)a;
	free(a);
	free(b);
	merged = malloc(128);
	TEST_ASSERT(merged != NULL);
	TEST_ASSERT((uintptr_t)merged == a_address);
	test_fill(merged, 128, 0x5a);
	TEST_ASSERT(test_memory_is(merged, 128, 0x5a));
	free(merged);
	free(c);
	return (0);
}

static int	allocate_blocks(void **ptrs, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		ptrs[i] = malloc(32 + (i % 4) * 16);
		if (!ptrs[i])
			return (1);
		test_fill(ptrs[i], 32 + (i % 4) * 16, (unsigned char)i);
		i++;
	}
	return (0);
}

int	test_free_orders(void)
{
	void	*ptrs[48];
	size_t	i;

	TEST_ASSERT(allocate_blocks(ptrs, 48) == 0);
	i = 0;
	while (i < 48)
		free(ptrs[i++]);
	TEST_ASSERT(allocate_blocks(ptrs, 48) == 0);
	i = 48;
	while (i > 0)
		free(ptrs[--i]);
	TEST_ASSERT(allocate_blocks(ptrs, 48) == 0);
	i = 0;
	while (i < 48)
	{
		free(ptrs[i]);
		i += 2;
	}
	i = 1;
	while (i < 48)
	{
		free(ptrs[i]);
		i += 2;
	}
	return (0);
}

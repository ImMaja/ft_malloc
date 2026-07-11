#include "test.h"

int	test_malloc_boundaries(void)
{
	const size_t	sizes[] = {
		1, 15, 16, 17, 127, 128, 129, 1023, 1024, 1025, 4096, 10000
	};
	const size_t	count = sizeof(sizes) / sizeof(sizes[0]);
	void			*ptr;
	size_t			i;

	i = 0;
	while (i < count)
	{
		ptr = malloc(sizes[i]);
		TEST_ASSERT(ptr != NULL);
		TEST_ASSERT((uintptr_t)ptr % _Alignof(max_align_t) == 0);
		test_fill(ptr, sizes[i], (unsigned char)(0x20 + i));
		TEST_ASSERT(test_memory_is(ptr, sizes[i],
				(unsigned char)(0x20 + i)));
		free(ptr);
		i++;
	}
	return (0);
}

int	test_malloc_independence(void)
{
	unsigned char	*a;
	unsigned char	*b;
	unsigned char	*c;

	a = malloc(31);
	b = malloc(257);
	c = malloc(1500);
	TEST_ASSERT(a != NULL && b != NULL && c != NULL);
	TEST_ASSERT(((uintptr_t)a + 31 <= (uintptr_t)b)
		|| ((uintptr_t)b + 257 <= (uintptr_t)a));
	TEST_ASSERT(((uintptr_t)a + 31 <= (uintptr_t)c)
		|| ((uintptr_t)c + 1500 <= (uintptr_t)a));
	TEST_ASSERT(((uintptr_t)b + 257 <= (uintptr_t)c)
		|| ((uintptr_t)c + 1500 <= (uintptr_t)b));
	test_fill(a, 31, 0x11);
	test_fill(b, 257, 0x22);
	test_fill(c, 1500, 0x33);
	TEST_ASSERT(test_memory_is(a, 31, 0x11));
	TEST_ASSERT(test_memory_is(b, 257, 0x22));
	TEST_ASSERT(test_memory_is(c, 1500, 0x33));
	free(a);
	free(b);
	free(c);
	return (0);
}

int	test_malloc_many(void)
{
	void	*ptrs[200];
	size_t	i;

	i = 0;
	while (i < 200)
	{
		ptrs[i] = malloc(64);
		TEST_ASSERT(ptrs[i] != NULL);
		test_fill(ptrs[i], 64, (unsigned char)i);
		i++;
	}
	i = 0;
	while (i < 200)
	{
		TEST_ASSERT(test_memory_is(ptrs[i], 64, (unsigned char)i));
		i++;
	}
	while (i > 0)
		free(ptrs[--i]);
	return (0);
}

int	test_malloc_invalid_sizes(void)
{
	size_t	huge;

	TEST_ASSERT(malloc(0) == NULL);
	huge = test_max_size();
	TEST_ASSERT(malloc(huge) == NULL);
	return (0);
}

int	test_calloc_zeroed(void)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = calloc(127, 7);
	TEST_ASSERT(ptr != NULL);
	i = 0;
	while (i < 127 * 7)
	{
		TEST_ASSERT(ptr[i] == 0);
		i++;
	}
	free(ptr);
	return (0);
}

int	test_calloc_overflow(void)
{
	size_t	nmemb;

	nmemb = test_max_size();
	TEST_ASSERT(calloc(nmemb, 2) == NULL);
	return (0);
}

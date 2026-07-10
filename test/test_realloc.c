#include "test.h"

int	test_realloc_special_cases(void)
{
	void		*ptr;
	void		*resized;
	uintptr_t	address;

	ptr = realloc(NULL, 64);
	TEST_ASSERT(ptr != NULL);
	test_fill(ptr, 64, 0x41);
	TEST_ASSERT(test_memory_is(ptr, 64, 0x41));
	free(ptr);
	ptr = malloc(64);
	TEST_ASSERT(ptr != NULL);
	TEST_ASSERT(realloc(ptr, 0) == NULL);
	ptr = malloc(17);
	TEST_ASSERT(ptr != NULL);
	test_fill(ptr, 17, 0x42);
	address = (uintptr_t)ptr;
	resized = realloc(ptr, 25);
	TEST_ASSERT(resized != NULL);
	TEST_ASSERT((uintptr_t)resized == address);
	TEST_ASSERT(test_memory_is(resized, 17, 0x42));
	free(resized);
	return (0);
}

int	test_realloc_shrink(void)
{
	void		*ptr;
	void		*resized;
	uintptr_t	address;

	ptr = malloc(112);
	TEST_ASSERT(ptr != NULL);
	test_fill(ptr, 112, 0x51);
	address = (uintptr_t)ptr;
	resized = realloc(ptr, 32);
	TEST_ASSERT(resized != NULL);
	TEST_ASSERT((uintptr_t)resized == address);
	TEST_ASSERT(test_memory_is(resized, 32, 0x51));
	free(resized);
	ptr = malloc(800);
	TEST_ASSERT(ptr != NULL);
	test_fill(ptr, 800, 0x52);
	address = (uintptr_t)ptr;
	resized = realloc(ptr, 100);
	TEST_ASSERT(resized != NULL);
	TEST_ASSERT((uintptr_t)resized == address);
	TEST_ASSERT(test_memory_is(resized, 100, 0x52));
	free(resized);
	return (0);
}

int	test_realloc_grow_in_place(void)
{
	void		*a;
	void		*b;
	void		*guard;
	void		*resized;
	uintptr_t	a_address;

	a = malloc(32);
	b = malloc(64);
	guard = malloc(32);
	TEST_ASSERT(a != NULL && b != NULL && guard != NULL);
	test_fill(a, 32, 0x61);
	test_fill(guard, 32, 0x62);
	a_address = (uintptr_t)a;
	free(b);
	resized = realloc(a, 96);
	TEST_ASSERT(resized != NULL);
	TEST_ASSERT((uintptr_t)resized == a_address);
	TEST_ASSERT(test_memory_is(resized, 32, 0x61));
	TEST_ASSERT(test_memory_is(guard, 32, 0x62));
	test_fill(resized, 96, 0x63);
	TEST_ASSERT(test_memory_is(resized, 96, 0x63));
	free(resized);
	free(guard);
	return (0);
}

int	test_realloc_grow_with_move(void)
{
	void		*a;
	void		*guard;
	void		*resized;
	uintptr_t	a_address;

	a = malloc(64);
	guard = malloc(64);
	TEST_ASSERT(a != NULL && guard != NULL);
	test_fill(a, 64, 0x71);
	test_fill(guard, 64, 0x72);
	a_address = (uintptr_t)a;
	resized = realloc(a, 512);
	TEST_ASSERT(resized != NULL);
	TEST_ASSERT((uintptr_t)resized != a_address);
	TEST_ASSERT(test_memory_is(resized, 64, 0x71));
	TEST_ASSERT(test_memory_is(guard, 64, 0x72));
	free(resized);
	free(guard);
	return (0);
}

static int	resize_and_check(void **ptr, size_t old_size, size_t new_size,
		unsigned char value)
{
	void	*resized;
	size_t	preserved;

	resized = realloc(*ptr, new_size);
	if (!resized)
		return (1);
	preserved = old_size;
	if (new_size < preserved)
		preserved = new_size;
	if (!test_memory_is(resized, preserved, value))
		return (1);
	test_fill(resized, new_size, value);
	*ptr = resized;
	return (0);
}

int	test_realloc_zone_transitions(void)
{
	void	*ptr;

	ptr = malloc(64);
	TEST_ASSERT(ptr != NULL);
	test_fill(ptr, 64, 0x7a);
	TEST_ASSERT(resize_and_check(&ptr, 64, 512, 0x7a) == 0);
	TEST_ASSERT(resize_and_check(&ptr, 512, 2048, 0x7a) == 0);
	TEST_ASSERT(resize_and_check(&ptr, 2048, 512, 0x7a) == 0);
	TEST_ASSERT(resize_and_check(&ptr, 512, 64, 0x7a) == 0);
	free(ptr);
	return (0);
}

int	test_realloc_large_shrink(void)
{
	void		*ptr;
	void		*resized;
	uintptr_t	address;

	ptr = malloc(10000);
	TEST_ASSERT(ptr != NULL);
	test_fill(ptr, 10000, 0x81);
	address = (uintptr_t)ptr;
	resized = realloc(ptr, 3000);
	TEST_ASSERT(resized != NULL);
	TEST_ASSERT((uintptr_t)resized == address);
	TEST_ASSERT(test_memory_is(resized, 3000, 0x81));
	ptr = resized;
	resized = realloc(ptr, 64);
	TEST_ASSERT(resized != NULL);
	TEST_ASSERT(test_memory_is(resized, 64, 0x81));
	free(resized);
	return (0);
}

int	test_realloc_failure(void)
{
	void	*ptr;
	void	*resized;
	size_t	huge;

	ptr = malloc(64);
	TEST_ASSERT(ptr != NULL);
	test_fill(ptr, 64, 0x91);
	huge = test_max_size();
	resized = realloc(ptr, huge);
	TEST_ASSERT(resized == NULL);
	TEST_ASSERT(test_memory_is(ptr, 64, 0x91));
	free(ptr);
	return (0);
}

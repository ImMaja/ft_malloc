#include "test.h"

#include <pthread.h>

#define THREAD_COUNT 8
#define THREAD_SLOT_COUNT 64
#define THREAD_OPERATION_COUNT 8000

typedef struct s_thread_slot
{
	void			*ptr;
	size_t			size;
	unsigned char	value;
} t_thread_slot;

typedef struct s_thread_context
{
	uint32_t	seed;
} t_thread_context;

static uint32_t	thread_random(uint32_t *state)
{
	*state = *state * 1664525u + 1013904223u;
	return (*state);
}

static size_t	thread_random_size(uint32_t *state)
{
	static const size_t	sizes[] = {
		1, 15, 16, 17, 63, 64, 127, 128, 129,
		511, 1023, 1024, 1025, 2048, 4096, 5000
	};
	const size_t		count = sizeof(sizes) / sizeof(sizes[0]);

	return (sizes[thread_random(state) % count]);
}

static int	thread_allocate(t_thread_slot *slot, uint32_t *state)
{
	slot->size = thread_random_size(state);
	slot->value = (unsigned char)(thread_random(state) | 1u);
	if (thread_random(state) % 4 == 0)
	{
		slot->ptr = calloc(1, slot->size);
		if (slot->ptr && !test_memory_is(slot->ptr, slot->size, 0))
			return (1);
	}
	else
		slot->ptr = malloc(slot->size);
	if (!slot->ptr)
		return (1);
	test_fill(slot->ptr, slot->size, slot->value);
	return (0);
}

static int	thread_resize(t_thread_slot *slot, uint32_t *state)
{
	void	*resized;
	size_t	new_size;
	size_t	preserved;

	new_size = thread_random_size(state);
	resized = realloc(slot->ptr, new_size);
	if (!resized)
		return (1);
	preserved = slot->size;
	if (new_size < preserved)
		preserved = new_size;
	if (!test_memory_is(resized, preserved, slot->value))
		return (1);
	slot->ptr = resized;
	slot->size = new_size;
	slot->value = (unsigned char)(thread_random(state) | 1u);
	test_fill(slot->ptr, slot->size, slot->value);
	return (0);
}

static int	thread_cleanup(t_thread_slot *slots)
{
	size_t	i;
	int		status;

	status = 0;
	i = 0;
	while (i < THREAD_SLOT_COUNT)
	{
		if (slots[i].ptr)
		{
			if (!test_memory_is(slots[i].ptr, slots[i].size,
					slots[i].value))
				status = 1;
			free(slots[i].ptr);
		}
		i++;
	}
	return (status);
}

static void	*thread_worker(void *arg)
{
	t_thread_context	*context;
	t_thread_slot		slots[THREAD_SLOT_COUNT];
	uint32_t			state;
	size_t				i;
	size_t				index;
	int					status;

	context = (t_thread_context *)arg;
	state = context->seed;
	memset(slots, 0, sizeof(slots));
	status = 0;
	i = 0;
	while (i < THREAD_OPERATION_COUNT && status == 0)
	{
		index = thread_random(&state) % THREAD_SLOT_COUNT;
		if (!slots[index].ptr)
			status = thread_allocate(&slots[index], &state);
		else if (!test_memory_is(slots[index].ptr, slots[index].size,
				slots[index].value))
			status = 1;
		else if (thread_random(&state) % 4 == 0)
		{
			free(slots[index].ptr);
			slots[index].ptr = NULL;
			slots[index].size = 0;
		}
		else
			status = thread_resize(&slots[index], &state);
		i++;
	}
	if (thread_cleanup(slots) != 0)
		status = 1;
	return ((void *)(uintptr_t)status);
}

int	test_thread_safety(void)
{
	pthread_t		threads[THREAD_COUNT];
	t_thread_context	contexts[THREAD_COUNT];
	void				*thread_status;
	size_t				created;
	size_t				i;
	int					status;

	created = 0;
	while (created < THREAD_COUNT)
	{
		contexts[created].seed = 0x42f00du
			+ (uint32_t)(created * 0x9e3779b9u);
		if (pthread_create(&threads[created], NULL, thread_worker,
				&contexts[created]) != 0)
			break ;
		created++;
	}
	status = (created != THREAD_COUNT);
	i = 0;
	while (i < created)
	{
		thread_status = NULL;
		if (pthread_join(threads[i], &thread_status) != 0
			|| thread_status != NULL)
			status = 1;
		i++;
	}
	TEST_ASSERT(status == 0);
	return (0);
}

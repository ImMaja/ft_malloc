#include "test.h"

#define STRESS_SLOT_COUNT 128
#define STRESS_OPERATION_COUNT 5000

typedef struct s_stress_slot
{
	void			*ptr;
	size_t			size;
	unsigned char	value;
} t_stress_slot;

static uint32_t	next_random(uint32_t *state)
{
	*state = *state * 1664525u + 1013904223u;
	return (*state);
}

static size_t	random_size(uint32_t *state)
{
	static const size_t	sizes[] = {
		1, 15, 16, 17, 63, 64, 127, 128, 129,
		511, 1023, 1024, 1025, 2048, 4096, 5000
	};
	const size_t		count = sizeof(sizes) / sizeof(sizes[0]);

	return (sizes[next_random(state) % count]);
}

static int	allocate_slot(t_stress_slot *slot, uint32_t *state)
{
	slot->size = random_size(state);
	slot->value = (unsigned char)(next_random(state) | 1u);
	slot->ptr = malloc(slot->size);
	if (!slot->ptr)
		return (1);
	test_fill(slot->ptr, slot->size, slot->value);
	return (0);
}

static int	resize_slot(t_stress_slot *slot, uint32_t *state)
{
	void	*resized;
	size_t	new_size;
	size_t	preserved;

	new_size = random_size(state);
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
	slot->value = (unsigned char)(next_random(state) | 1u);
	test_fill(slot->ptr, slot->size, slot->value);
	return (0);
}

int	test_stress(void)
{
	t_stress_slot	slots[STRESS_SLOT_COUNT];
	uint32_t		state;
	size_t			i;
	size_t			index;

	memset(slots, 0, sizeof(slots));
	state = 0x42f00du;
	i = 0;
	while (i < STRESS_OPERATION_COUNT)
	{
		index = next_random(&state) % STRESS_SLOT_COUNT;
		if (!slots[index].ptr)
			TEST_ASSERT(allocate_slot(&slots[index], &state) == 0);
		else
		{
			TEST_ASSERT(test_memory_is(slots[index].ptr, slots[index].size,
					slots[index].value));
			if (next_random(&state) % 3 == 0)
			{
				free(slots[index].ptr);
				slots[index].ptr = NULL;
				slots[index].size = 0;
			}
			else
				TEST_ASSERT(resize_slot(&slots[index], &state) == 0);
		}
		i++;
	}
	i = 0;
	while (i < STRESS_SLOT_COUNT)
	{
		if (slots[i].ptr)
		{
			TEST_ASSERT(test_memory_is(slots[i].ptr, slots[i].size,
					slots[i].value));
			free(slots[i].ptr);
		}
		i++;
	}
	return (0);
}

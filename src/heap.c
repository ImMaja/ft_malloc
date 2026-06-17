#include <unistd.h>

#include "../include/alloc.h"

static t_heap	g_heap = {NULL, NULL, NULL};

t_heap	*get_heap(void)
{
	return (&g_heap);
}

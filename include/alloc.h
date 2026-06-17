#ifndef ALLOC_H
# define ALLOC_H

# include <stddef.h>

# define TINY_BLOCK_SIZE 128
# define SMALL_BLOCK_SIZE 1024

# define ALIGN_UP(x) (((x) + 15) & ~15)

# define BLOCK_HEADER_SIZE ALIGN_UP(sizeof(t_block))
# define ZONE_HEADER_SIZE ALIGN_UP(sizeof(t_zone))

typedef enum e_zone_type
{
	TINY,
	SMALL,
	LARGE
}	t_zone_type;


typedef struct s_block
{
	size_t			size;	// Usable block size (without t_block header)
	int				free;
	struct s_block	*next;
	struct s_block	*prev;
}	t_block;

typedef struct s_zone
{
	t_zone_type		type;
	size_t			size;	// total zone size
	t_block			*block;
	struct s_zone	*next;
	struct s_zone	*prev;
}	t_zone;

typedef struct s_heap
{
	t_zone	*tiny;
	t_zone	*small;
	t_zone	*large;
}	t_heap;


/** malloc.c */
void	*malloc(size_t size);

/** heap.c */
t_heap	*get_heap(void);
t_zone	*get_zone_ptr_by_type(const t_zone_type type);

/** zone.c */
int		create_new_zone(const t_zone_type type, const size_t size);

#endif /** ALLOC_H */

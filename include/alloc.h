#ifndef ALLOC_H
# define ALLOC_H

# include <stddef.h>
# include <stdbool.h>

/** Align number to 16 macro */
# define ALIGN_UP(x) (((x) + 15) & ~15)

/** Define sizes of t_zone and t_block header aligned to 16 */
# define BLOCK_HEADER_SIZE ALIGN_UP(sizeof(t_block))
# define ZONE_HEADER_SIZE ALIGN_UP(sizeof(t_zone))

/** Define zone threshold */
# define TINY_BLOCK_SIZE 128
# define SMALL_BLOCK_SIZE 1024

/** Min payload size */
# define MIN_PAYLOAD_SIZE 16

/**
 * Define the minimal requiered size to split a block
 * Used when the size of a realloc is smaller then the block_size
*/
# define MIN_SPLIT_SIZE (BLOCK_HEADER_SIZE + MIN_PAYLOAD_SIZE)

/** Define number of elements of heap struct */
# define HEAP_ELEM 3

/** Define min number of blocks for TINY and SMALL zones */
# define ZONE_ALLOC_COUNT 100


typedef enum e_zone_type
{
	TINY,
	SMALL,
	LARGE
}	t_zone_type;


typedef struct s_block
{
	size_t			payload_size;
	int				free;
	struct s_block	*next;
	struct s_block	*prev;
}	t_block;

typedef struct s_zone
{
	t_zone_type		type;
	size_t			size;		// Total zone size (including all headers and payloads)
	t_block			*blocks;	// First block ptr
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
void		*malloc(size_t size);

/** realloc.c */
void		*realloc(void *ptr, size_t size);

/** free.c */
void		free(void *tr);

/** show_alloc_mem.c */
void		show_alloc_mem(void);

/** heap.c */
t_heap		*get_heap(void);
t_zone		**get_zone_ptr_by_type(const t_zone_type type);

/** zone.c */
t_zone		*create_new_zone(const t_zone_type type, const size_t size);

/** zone_utils.c */
t_zone_type	get_zone_type_by_size(const size_t size);
void		push_new_zone_in_linked_list(t_zone **heap_zone, t_zone *new_zone);
size_t		calculate_zone_length(const t_zone_type type, const size_t size);
void		init_zone_header(t_zone *mem, const t_zone_type type, const size_t size);

/** block.c */
void		create_default_block(t_zone *zone);
t_block		*find_available_block(const t_zone *zone, const size_t size);
void		*split_block(t_block *split, const size_t size);

/** block_utils.c */
t_zone		*find_zone_from_payload_ptr(const void *ptr);
t_block		*find_block_from_payload_ptr(const t_zone *zone, const void *payload_ptr);

/** utils/ */
void		ft_putnbr_fd(int n, int fd);

#endif /** ALLOC_H */

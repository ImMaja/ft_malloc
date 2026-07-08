#ifndef ALLOC_H
# define ALLOC_H

# include <stddef.h>
# include <stdbool.h>

/** Align number to 16 macro */
#define ALIGNMENT 16
#define ALIGN_UP(x) (((x) + (ALIGNMENT - 1)) & ~((size_t)ALIGNMENT - 1))

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
	size_t			size;
	t_block			*blocks;
	struct s_zone	*next;
	struct s_zone	*prev;
}	t_zone;

typedef struct s_allocator
{
	t_zone	*zones;
	size_t	page_size;
}	t_allocator;

/** malloc.c */
void		*malloc(size_t size);

/** realloc.c */
void		*realloc(void *ptr, size_t size);

/** free.c */
void		free(void *ptr);

/** show_alloc_mem.c */
void		show_alloc_mem(void);

/** allocator.c */
t_zone		**get_zones(void);
size_t		get_page_size(void);

/** align.c */
int			normalize_size(size_t *size);

/** zone.c */
t_zone		*create_new_zone(const t_zone_type type, const size_t size);
t_zone		*find_zone_from_payload_ptr(const void *ptr);

/** zone_utils.c */
t_zone_type	get_zone_type_by_size(const size_t size);
size_t		calculate_zone_length(const t_zone_type type, const size_t size);
void		push_zone(t_zone *new_zone);

/** block.c */
void		create_default_block(t_zone *zone, const size_t size);
t_block		*find_free_block(const t_zone_type type, const size_t size);
void		split_block(t_block *block, const size_t size);
t_block		*find_block_from_payload_ptr(const t_zone *zone, const void *payload_ptr);

/** block_utils.c */


/** utils/ */
void		*ft_memcpy(void *dest, const void *src, size_t n);

#endif /** ALLOC_H */

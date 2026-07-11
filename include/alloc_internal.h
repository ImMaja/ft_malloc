#ifndef ALLOC_INTERNAL_H
# define ALLOC_INTERNAL_H

# include "ft_malloc.h"

# include <stdint.h>
# include <pthread.h>

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

/** Define the minimal requiered size for a block */
# define MIN_BLOCK_SIZE (BLOCK_HEADER_SIZE + MIN_PAYLOAD_SIZE)

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
	size_t			used_blocks;
	t_block			*blocks;
	struct s_zone	*next;
	struct s_zone	*prev;
}	t_zone;

typedef struct s_allocator
{
	t_zone			*zones;
	size_t			page_size;
	pthread_mutex_t	alloc_mutex;

}	t_allocator;


/** malloc/malloc_internal.c */
void			*malloc_internal(const size_t size);

/** realloc/realloc_internal.c */
void			*realloc_internal(void *ptr, const size_t size);

/** free/free_internal.c */
void			free_internal(void *ptr);

/** show_alloc_mem/show_alloc_mem_internal.c */
void			show_alloc_mem_internal(void);

/** allocator.c */
t_zone			**get_zones(void);
size_t			get_page_size(void);
pthread_mutex_t	*get_alloc_mutex(void);

/** align.c */
int				normalize_size(size_t *size);
size_t			align_page(const size_t size);

/** zone.c */
t_zone			*create_new_zone(const t_zone_type type, const size_t size);
t_zone			*find_zone_from_payload_ptr(const void *ptr);
int				reduce_large_zone_size(t_zone *zone, const size_t realloc_size, const size_t new_zone_size);
int				delete_zone(t_zone *zone);

/** zone_utils.c */
t_zone_type		get_zone_type_by_size(const size_t size);
size_t			calculate_zone_size(const t_zone_type type, const size_t size);
void			push_zone(t_zone *new_zone);
void			unlink_zone(t_zone *prev, t_zone *next);
t_zone			*find_empty_zone(const t_zone_type type, const t_zone *exclude);

/** block.c */
int				create_default_block(t_zone *zone);
void			split_block(t_block *block, const size_t size);
int				inplace_grow(t_block *block, const size_t new_size);

/** block_utils.c */
int				find_free_block(const t_zone_type type, const size_t size, t_zone **out_zone, t_block **out_block);
void			merge_free_blocks(t_block *block);
t_block			*find_block_from_payload_ptr(const t_zone *zone, const void *payload_ptr);

/** utils/ */
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
void			put_str(const char *s);
void			put_size(size_t n);
void			put_addr(uintptr_t addr);

#endif /** ALLOC_INTERNAL_H */

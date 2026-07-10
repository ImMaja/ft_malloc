#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stddef.h>

/** malloc/malloc.c */
__attribute__((visibility("default")))
void	*malloc(size_t size);

/** realloc/realloc.c */
__attribute__((visibility("default")))
void	*realloc(void *ptr, size_t size);

/** calloc/calloc.c */
__attribute__((visibility("default")))
void	*calloc(size_t nmemb, size_t size);

/** free/free.c */
__attribute__((visibility("default")))
void	free(void *ptr);

/** show_alloc_mem/show_alloc_mem.c */
__attribute__((visibility("default")))
void	show_alloc_mem(void);

#endif /** FT_MALLOC_H */

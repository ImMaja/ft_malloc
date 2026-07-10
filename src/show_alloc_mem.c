#include <stdint.h>
#include <unistd.h>

#include "../include/alloc.h"


static char		*get_str_type(const t_zone_type type);
static t_zone	*find_next_zone(const uintptr_t last);
static void		print_zone_header(t_zone *zone);
static void		print_block_line(t_block *block);
static void		print_total(size_t bytes_count, const size_t blocks_count);


/**
 * @brief Show all allocated zone in ascending order
 */
void	show_alloc_mem(void)
{
	uintptr_t	last = 0;
	t_zone		*z = NULL;
	t_block		*b = NULL;
	size_t		bytes_count = 0;
	size_t		blocks_count = 0;

	while ( ( z = find_next_zone(last) ) != NULL )
	{
		print_zone_header(z);
		b = z->blocks;
		if (!b)
			write(1, "Empty zone\n", 11);
		while (b)
		{
			if (b->free == 0)
			{
				print_block_line(b);
				bytes_count += b->payload_size;
				blocks_count++;
			}
			b = b->next;
		}
		last = (uintptr_t) z;
	}
	print_total(bytes_count, blocks_count);
}


/**
 * @brief Get the type of a zone in a string
 * ex: TINY -> "TINY"
 */
static char	*get_str_type(const t_zone_type type)
{
	if (type == TINY)
		return ("TINY");
	else if (type == SMALL)
		return ("SMALL");
	else if (type == LARGE)
		return ("LARGE");
	return ("???");
}


/**
 * @brief Iterate on zones linked-list to retrieve
 * next zone to print by incresing memory address
 * @param last The previous zone address
 */
static t_zone	*find_next_zone(const uintptr_t last)
{
	t_zone		*z = *get_zones();
	t_zone		*best = NULL;
	uintptr_t	best_addr = UINTPTR_MAX;

	while (z)
	{
		if ( (uintptr_t) z > last && (uintptr_t) z < best_addr )
		{
			best = z;
			best_addr = (uintptr_t) z;
		}
		z = z->next;
	}

	return (best);
}


/**
 * @brief Print zone type and beginning address
 * @param zone The zone to print
 */
static void	print_zone_header(t_zone *zone)
{
	put_str(get_str_type(zone->type));
	put_str(" : ");
	put_addr((uintptr_t)zone);
	put_str("\n");
}


/**
 * @brief Print block range addresses and size
 * @param block The block to print
 */
static void	print_block_line(t_block *block)
{
	uintptr_t	start;
	uintptr_t	end;

	start = (uintptr_t)block + BLOCK_HEADER_SIZE;
	end = start + block->payload_size;

	put_addr(start);
	put_str(" - ");
	put_addr(end);
	put_str(" : ");
	put_size(block->payload_size);
	put_str(" bytes\n");
}


/**
 * @brief Print the sum of all payloads
 * @param total The total size of payloads
 */
static void	print_total(size_t bytes_count, const size_t blocks_count)
{
	put_str("Total of ");
	put_size(bytes_count);
	put_str(" bytes in ");
	put_size(blocks_count);
	put_str(" blocks\n");
}

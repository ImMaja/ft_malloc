#include <stdint.h>
#include <unistd.h>

#include "alloc_internal.h"

static void	put_hex(uintptr_t n);



void	put_str(const char *s)
{
	size_t	len;

	if (!s)
		return ;
	len = 0;
	while (s[len])
		len++;
	if (len > 0)
		write(1, s, len);
}

void	put_size(size_t n)
{
	char	buffer[20];
	size_t	i;

	i = sizeof(buffer);
	if (n == 0)
	{
		write(1, "0", 1);
		return ;
	}
	while (n > 0)
	{
		buffer[--i] = (char)('0' + (n % 10));
		n /= 10;
	}
	write(1, &buffer[i], sizeof(buffer) - i);
}

static void	put_hex(uintptr_t n)
{
	const char	base[] = "0123456789abcdef";
	char		buffer[sizeof(uintptr_t) * 2];
	size_t		i;

	i = sizeof(buffer);
	if (n == 0)
	{
		write(1, "0", 1);
		return ;
	}
	while (n > 0)
	{
		buffer[--i] = base[n % 16];
		n /= 16;
	}
	write(1, &buffer[i], sizeof(buffer) - i);
}

void	put_addr(uintptr_t addr)
{
	put_str("0x");
	put_hex(addr);
}

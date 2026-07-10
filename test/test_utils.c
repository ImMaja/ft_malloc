#include "test.h"

static size_t	str_length(const char *str)
{
	size_t	length;

	length = 0;
	while (str && str[length])
		length++;
	return (length);
}

static void	put_number(unsigned int number)
{
	char	buffer[16];
	size_t	i;

	i = sizeof(buffer);
	if (number == 0)
	{
		write(STDERR_FILENO, "0", 1);
		return ;
	}
	while (number != 0)
	{
		buffer[--i] = (char)('0' + number % 10);
		number /= 10;
	}
	write(STDERR_FILENO, buffer + i, sizeof(buffer) - i);
}

void	test_putstr(const char *str)
{
	if (str)
		write(STDOUT_FILENO, str, str_length(str));
}

int	test_failure(const char *condition, const char *file, int line)
{
	write(STDERR_FILENO, "FAIL\n  at ", 10);
	write(STDERR_FILENO, file, str_length(file));
	write(STDERR_FILENO, ":", 1);
	put_number((unsigned int)line);
	write(STDERR_FILENO, "\n  assertion: ", 14);
	write(STDERR_FILENO, condition, str_length(condition));
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

int	test_memory_is(const void *ptr, size_t size, unsigned char value)
{
	const unsigned char	*bytes;
	size_t				i;

	if (!ptr)
		return (0);
	bytes = ptr;
	i = 0;
	while (i < size)
	{
		if (bytes[i] != value)
			return (0);
		i++;
	}
	return (1);
}

void	test_fill(void *ptr, size_t size, unsigned char value)
{
	unsigned char	*bytes;
	size_t			i;

	bytes = ptr;
	i = 0;
	while (i < size)
	{
		bytes[i] = value;
		i++;
	}
}

size_t	test_max_size(void)
{
	return (SIZE_MAX);
}

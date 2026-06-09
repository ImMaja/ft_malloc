/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maja <maja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:29:33 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/06/16 16:45:51 by maja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static void	realloc_line(t_line *line,
			size_t line_size,
			size_t new_line_size)
{
	line->line = (char *) ft_realloc((void *) line->line,
			sizeof(char) * line_size,
			sizeof(char) * new_line_size);
}

static bool	fill_line(t_line *line,
				t_buffer *buffer)
{
	while (buffer->buf_iter < BUFFER_SIZE)
	{
		*(line->line + line->line_iter) = *(buffer->buffer + buffer->buf_iter);
		if (*(buffer->buffer + buffer->buf_iter) == '\n')
		{
			buffer->buf_iter++;
			return (true);
		}
		if (*(buffer->buffer + buffer->buf_iter) == '\0')
		{
			buffer->buf_iter = 0;
			return (true);
		}
		buffer->buf_iter++;
		line->line_iter++;
	}
	return (false);
}

static ssize_t	fill_buffer(int fd,
					t_buffer *buffer,
					t_line *line,
					size_t *refill)
{
	ssize_t	read_status;

	read_status = 1;
	if (buffer->buf_iter == 0 || buffer->buf_iter == BUFFER_SIZE)
	{
		buffer->buf_iter = 0;
		read_status = read(fd, (void *) buffer->buffer, BUFFER_SIZE);
		if (read_status == -1)
		{
			ft_bzero((void *) buffer->buffer, BUFFER_SIZE);
			if (line->line != NULL)
				free(line->line);
		}
		else if (read_status == 0 && fd == 0)
			return (-1);
		else
		{
			*(buffer->buffer + read_status) = '\0';
			(*refill)++;
		}
	}
	return (read_status);
}

static char	*return_line(int fd,
				t_buffer *buffer,
				t_line *line,
				size_t refill)
{
	if (fd == 0)
		buffer->buf_iter = 0;
	if (*(line->line) == '\0')
		return (free(line->line), NULL);
	realloc_line(line, (refill + 1) * BUFFER_SIZE, line->line_iter + 2);
	if (line->line == NULL)
		return (NULL);
	*(line->line + line->line_iter + 1) = '\0';
	return (line->line);
}

char	*get_next_line(int fd)
{
	static t_buffer	buffer;
	t_line			line;	
	size_t			refill;

	if (fd < 0 || fd > 1023)
		return (NULL);
	if (fd == 0)
		buffer.buf_iter = 0;
	line.line = NULL;
	line.line_iter = 0;
	refill = 0;
	while (1)
	{
		if (fill_buffer(fd, &buffer, &line, &refill) == -1)
			return (NULL);
		realloc_line(&line, refill * BUFFER_SIZE, (refill + 1) * BUFFER_SIZE);
		if (line.line == NULL)
			return (NULL);
		if (fill_line(&line, &buffer))
			return (return_line(fd, &buffer, &line, refill));
	}
	return (NULL);
}

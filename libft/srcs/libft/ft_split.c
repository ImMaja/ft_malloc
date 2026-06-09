/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maja <maja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:13:40 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/05/13 16:17:53 by maja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	free_all_str(char **arr, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static size_t	count_str_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*(s + i) != '\0' && *(s + i) != c)
		i++;
	return (i);
}

size_t	count_strs(char const *s, char c)
{
	size_t	i;
	size_t	delimitor_counter;

	i = 0;
	delimitor_counter = 0;
	if (*(s) == '\0')
		return (0);
	while (*(s + i) == c)
		i++;
	while (*(s + i) != '\0')
	{
		if (*(s + i) == c)
		{
			while (*(s + i) == c)
				i++;
			if (*(s + i) != '\0')
				delimitor_counter++;
		}
		else
			i++;
	}
	return (delimitor_counter + 1);
}

static	char	**calc(char const *s, char c, char **arr)
{
	size_t	i;
	size_t	j;
	size_t	curr_str;

	i = 0;
	curr_str = 0;
	while (*(s + i) != '\0')
	{
		while (*(s + i) == c)
			i++;
		if (*(s + i) != '\0')
		{
			j = 0;
			arr[curr_str] = malloc(sizeof(char) * count_str_len(s + i, c) + 1);
			if (arr[curr_str] == 0)
				return (free_all_str(arr, curr_str), NULL);
			while (*(s + i) != c && *(s + i) != '\0')
				arr[curr_str][j++] = *(s + i++);
			arr[curr_str][j] = '\0';
			curr_str++;
		}
	}
	arr[curr_str] = 0;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	if (!s)
		return (0);
	arr = (char **) malloc(sizeof(char *) * (count_strs(s, c) + 1));
	if (arr == 0)
		return (0);
	return (calc(s, c, arr));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maja <maja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:18:22 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/05/13 16:17:53 by maja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static	int	is_in_set(char c, char *set)
{
	size_t	i;

	i = 0;
	while (*(set + i) != '\0')
	{
		if (*(set + i) == c)
			return (1);
		i++;
	}
	return (0);
}

static	size_t	count_chars_(char const *s1, char const *set, size_t s1_len)
{
	size_t	i;
	size_t	cpt;

	i = 0;
	cpt = 0;
	while (*(s1 + i) != '\0' && is_in_set(*(s1 + i), (char *)set) == 1)
	{
		i++;
		cpt++;
	}
	i = s1_len - 1;
	while (*(s1 + i) > 0 && is_in_set(*(s1 + i), (char *)set) == 1)
	{
		i--;
		cpt++;
	}
	if (cpt >= s1_len)
		return (0);
	return (s1_len - cpt);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	size_t	s1_len;
	size_t	s_len;
	size_t	i;
	size_t	j;

	if (s1 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s_len = count_chars_(s1, set, s1_len);
	s = (char *) malloc(sizeof(char) * s_len + 1);
	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (is_in_set(*(s1 + i), (char *)set) == 1)
		i++;
	while (j < s_len)
	{
		*(s + j) = *(s1 + i + j);
		j++;
	}
	*(s + j) = '\0';
	return (s);
}

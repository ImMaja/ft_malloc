/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maja <maja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 10:58:06 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/09/16 00:44:50 by maja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static	char	*calc(char const *s1, char const *s2, char *s3)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (*(s1 + j) != '\0')
	{
		*(s3 + i) = *(s1 + j);
		i++;
		j++;
	}
	j = 0;
	while (*(s2 + j) != '\0')
	{
		*(s3 + i) = *(s2 + j);
		i++;
		j++;
	}
	*(s3 + i) = '\0';
	return (s3);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;

	if (s1 == 0 || s2 == 0)
		return (0);
	s3 = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (s3 == NULL)
		return (NULL);
	return (calc(s1, s2, s3));
}

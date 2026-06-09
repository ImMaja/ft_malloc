/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maja <maja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:49:05 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/05/13 16:17:53 by maja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*s2;

	if (!s || !f)
		return (0);
	i = 0;
	s2 = (char *) malloc(sizeof(char) + ft_strlen(s));
	if (s2 == NULL)
		return (NULL);
	while (*(s + i) != '\0')
	{
		*(s2 + i) = (f)(i, *(s + i));
		i++;
	}
	*(s2 + i) = '\0';
	return (s2);
}

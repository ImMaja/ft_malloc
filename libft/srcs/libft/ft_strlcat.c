/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maja <maja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:18:41 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/05/13 16:17:53 by maja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t count)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	if (count == 0)
		return (ft_strlen(src));
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = 0;
	j = dest_len;
	if (count <= dest_len)
		return (count + src_len);
	while (j < count - 1 && *(src + i) != '\0')
	{
		*(dest + j) = *(src + i);
		j++;
		i++;
	}
	*(dest + j) = '\0';
	return (dest_len + src_len);
}

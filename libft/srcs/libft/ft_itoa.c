/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maja <maja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 08:10:57 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/09/16 00:41:48 by maja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static	int	count_char(int n)
{
	int		i;
	long	nb;

	nb = n;
	i = 0;
	if (n < 0)
	{
		nb *= -1;
		i++;
	}
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	return (i + 1);
}

static	char	*rev_tab(char *s, int size)
{
	int		i;
	char	tmp;

	i = 0;
	while (i < size / 2 + 1)
	{
		tmp = *(s + i);
		*(s + i) = *(s + size - i);
		*(s + size - i) = tmp;
		i++;
	}
	return (s);
}

static	char	*calc(char *s, long nb)
{
	int		sign;
	int		i;

	sign = 1;
	i = 0;
	if (nb == 0)
		*(s + i++) = '0';
	if (nb < 0)
	{
		nb *= -1;
		sign = -1;
	}
	while (nb > 0)
	{
		*(s + i++) = (nb % 10) + '0';
		nb /= 10;
	}
	if (sign != 1)
		*(s + i++) = '-';
	*(s + i) = '\0';
	return (rev_tab(s, i - 1));
}

char	*ft_itoa(int n)
{
	char	*s;
	long	nb;

	nb = n;
	s = malloc(sizeof(char) * (count_char(nb) + 1));
	if (s == NULL)
		return (0);
	calc(s, nb);
	return (s);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maja <maja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:39:18 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/05/13 16:17:53 by maja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	ft_strlen_(char *s)
{
	int	i;

	if (!s || *(s) == 0)
		return (0);
	i = 0;
	while (*(s + i) != '\0')
		i++;
	return (i);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	len;

	if (!s)
		return (ft_putstr("(null)"));
	len = ft_strlen_(s);
	write(1, s, len);
	return (len);
}

int	print_positive_nb(unsigned int dec)
{
	print_positive_base((unsigned long long)dec, "0123456789", 10);
	return (count_chars(dec, 10));
}

int	print_nb(int dec)
{
	char	*h;

	h = "0123456789";
	if (dec == 0)
		return (ft_putchar('0'));
	if (dec < 0)
	{
		ft_putchar('-');
		print_positive_base((unsigned long long)dec * -1, h, 10);
		return (count_chars((unsigned long long)dec * -1, 10) + 1);
	}
	print_positive_base(dec, h, 10);
	return (count_chars(dec, 10));
}

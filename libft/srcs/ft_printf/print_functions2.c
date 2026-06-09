/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maja <maja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:50:22 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/05/13 16:17:53 by maja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	print_prefixed_hexa(unsigned long long dec)
{
	size_t	len;

	len = 0;
	if (dec == 0)
		return (ft_putstr("(nil)"));
	len += ft_putstr("0x");
	len += count_chars(dec, 16);
	print_positive_base(dec, "0123456789abcdef", 16);
	return (len);
}

int	print_hexa(unsigned int dec, int upper)
{
	size_t	len;
	char	*h;

	h = "0123456789abcdef";
	if (upper == 1)
		h = "0123456789ABCDEF";
	len = 0;
	if (dec == 0)
		return (ft_putchar('0'));
	len += count_chars(dec, 16);
	print_positive_base(dec, h, 16);
	return (len);
}

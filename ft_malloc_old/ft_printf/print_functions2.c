/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:50:22 by gpeiffer          #+#    #+#             */
/*   Updated: 2023/11/25 17:52:19 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

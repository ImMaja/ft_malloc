/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maja <maja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:32:15 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/05/13 16:17:53 by maja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	count_chars(unsigned long long dec, int b_len)
{
	size_t	i;

	i = 0;
	while (dec >= (unsigned long long)b_len)
	{
		dec /= b_len;
		i++;
	}
	return (i + 1);
}

void	print_positive_base(unsigned long long dec, char *base, int b_len)
{
	if (dec >= (unsigned long long)b_len)
	{
		print_positive_base(dec / b_len, base, b_len);
		print_positive_base(dec % b_len, base, b_len);
	}
	else
		ft_putchar(base[dec]);
}

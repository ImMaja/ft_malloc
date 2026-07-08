/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:47:52 by gpeiffer          #+#    #+#             */
/*   Updated: 2023/11/25 18:11:54 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>

int		ft_printf(const char *format, ...);
int		iter_format(const char *f, va_list args, size_t i, size_t l);
int		ft_strlen(char *s);
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		print_nb(int dec);
int		print_positive_nb(unsigned int dec);
int		print_prefixed_hexa(unsigned long long dec);
int		print_hexa(unsigned int dec, int upper);
int		count_chars(unsigned long long dec, int b_len);
void	print_positive_base(unsigned long long dec, char *base, int b_len);

#endif
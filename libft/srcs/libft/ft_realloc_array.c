/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maja <maja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 08:52:03 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/05/13 16:17:53 by maja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	**ft_realloc_array(void **arr_ptr,
						size_t arr_ptr_size,
						size_t new_arr_ptr_size)
{
	void	**new_arr_ptr;

	new_arr_ptr = (void **) malloc(new_arr_ptr_size);
	if (new_arr_ptr == NULL)
	{
		if (arr_ptr != NULL)
			ft_free_array(arr_ptr);
		return (NULL);
	}
	if (arr_ptr == NULL)
		return (new_arr_ptr);
	if (arr_ptr_size > new_arr_ptr_size)
		ft_memcpy_opti_af(new_arr_ptr, arr_ptr, new_arr_ptr_size);
	else
		ft_memcpy_opti_af(new_arr_ptr, arr_ptr, arr_ptr_size);
	free(arr_ptr);
	return (new_arr_ptr);
}

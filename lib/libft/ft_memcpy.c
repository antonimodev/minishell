/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:23:24 by antonimo          #+#    #+#             */
/*   Updated: 2024/04/30 15:27:29 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*src2;

	src2 = src;
	i = 0;
	if (src == NULL && dst == NULL)
		return (0);
	while (i < n)
	{
		((unsigned char *)dst)[i] = src2[i];
		i++;
	}
	return (dst);
}

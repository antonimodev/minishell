/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:06:30 by antonimo          #+#    #+#             */
/*   Updated: 2024/04/30 15:16:42 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*ptr2;
	const unsigned char	*ptr1;

	i = -1;
	ptr1 = (const unsigned char *)src;
	ptr2 = (unsigned char *)dst;
	if (src == NULL && dst == NULL)
		return (0);
	if (ptr2 > ptr1)
	{
		while (n != 0)
		{
			n--;
			ptr2[n] = ptr1[n];
		}
	}
	else
	{
		while (++i < n)
			ptr2[i] = ptr1[i];
	}
	return (dst);
}

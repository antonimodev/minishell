/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:44:09 by antonimo          #+#    #+#             */
/*   Updated: 2024/04/18 12:13:52 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	while (i < n && ptr1[i] && ptr2[i])
	{
		if (ptr1[i] != ptr2[i])
			return ((int)(ptr1[i] - ptr2[i]));
		i++;
	}
	if (i < n)
		return ((int)(ptr1[i] - ptr2[i]));
	return (0);
}

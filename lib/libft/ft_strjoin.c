/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:24:01 by antonimo          #+#    #+#             */
/*   Updated: 2024/04/22 10:38:44 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			i;
	size_t			j;
	size_t			stotal;
	unsigned char	*ptr;

	i = 0;
	j = 0;
	stotal = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc((stotal + 1) * sizeof(char));
	if (ptr == NULL || s1 == NULL || s2 == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		ptr[i + j] = s2[j];
		j++;
	}
	ptr[i + j] = '\0';
	return ((char *)ptr);
}

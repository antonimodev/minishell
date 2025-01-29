/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:38:18 by antonimo          #+#    #+#             */
/*   Updated: 2024/04/22 12:41:21 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int chr)
{
	int	strlen;

	strlen = ft_strlen(str);
	if ((char)chr == '\0')
		return ((char *)(str + strlen));
	while (strlen >= 0)
	{
		if (str[strlen] == (char)chr)
			return ((char *)(str + strlen));
		strlen--;
	}
	return (NULL);
}

/* 
- We've casted the returned pointer because function
request a pointer with char type.
*/
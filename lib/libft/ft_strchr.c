/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:37:41 by antonimo          #+#    #+#             */
/*   Updated: 2024/04/22 12:38:52 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int chr)
{
	int	i;

	i = 0;
	if ((char)chr == '\0')
		return ((char *)(str + ft_strlen(str)));
	while (str[i] != '\0')
	{
		if (str[i] == (char)chr)
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}

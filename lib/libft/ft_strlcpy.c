/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:48:27 by antonimo          #+#    #+#             */
/*   Updated: 2024/04/16 11:11:30 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t			i;

	i = 0;
	if (n != 0)
	{
		while (src[i] != '\0' && i < n - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

/* int	main(void)
{
	char	str[20];
	char	str2[20];

	printf("Resultado de mi funcion; %lu.\n", ft_strlcpy(str,"hola", 3));
	printf("Resultado de mi funcion; %lu.\n", strlcpy(str2,"hola", 3));
	printf("Mi función es: %s.\n", str);
	printf("Mi función es: %s.\n", str2);
} */

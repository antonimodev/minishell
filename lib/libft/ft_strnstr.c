/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:51:19 by antonimo          #+#    #+#             */
/*   Updated: 2024/04/12 14:07:40 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	ptr = (char *)haystack;
	if (*needle == '\0')
		return (ptr);
	while (haystack[i] != '\0' && i < n)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < n)
		{
			j++;
			if (needle[j] == '\0')
				return (ptr + i);
		}
		i++;
	}
	return (NULL);
}

/* int	main(void)
{
	const char	str[20] = "hola que tal";
	const char	str2[20] = "";

	printf("resultado; %s\n", ft_strnstr(str, str2, 5));
	printf("real; %s", strnstr(str, str2, 5));
}
 */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:01:49 by antonimo          #+#    #+#             */
/*   Updated: 2024/04/23 10:35:58 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;
	unsigned int	slen;

	i = 0;
	slen = (ft_strlen(s));
	str = malloc((slen + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (s == NULL)
		return (NULL);
	while (i < slen)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*Tenemos que utilizar el puntero a la función
"f" que recibe los parametros unsigned int y char
para utilizarlos en cada caracter de s.*/
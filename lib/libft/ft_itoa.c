/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:56:44 by antonimo          #+#    #+#             */
/*   Updated: 2024/04/24 16:46:13 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_countdigits(int n)
{
	int	nlen;

	nlen = 0;
	if (n <= 0)
		nlen++;
	while (n != 0)
	{
		n = n / 10;
		nlen ++;
	}
	return (nlen);
}

char	*ft_itoa(int n)
{
	int		count;
	long	num;
	char	*str;

	num = n;
	count = ft_countdigits(n);
	str = (char *) malloc((ft_countdigits(n) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (n < 0)
		num = -num;
	str[count] = '\0';
	count--;
	while (count >= 0)
	{
		str[count] = (num % 10) + '0';
		count--;
		num = num / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

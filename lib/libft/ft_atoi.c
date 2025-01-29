/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:30:19 by antonimo          #+#    #+#             */
/*   Updated: 2024/04/22 16:19:14 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char chr)
{
	if (chr == '\t' || chr == '\n' || chr == '\r' || \
		chr == '\v' || chr == ' ' || chr == '\f')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	number;
	int	neg;

	i = 0;
	number = 0;
	neg = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-')
	{
		neg = -neg;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) == 1)
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	return (number * neg);
}

/* int	main(void)
{
	const char	str[] = " -23-2k1020";
	const char	str1[] = " 23 45";
	const char	str2[] = " -+23";
	const char	str3[] = "+23";
	const char	str4[] = "++23";
	const char	str5[] = "+ 23";

	printf("FT_ATOI; %i\n", ft_atoi(str));
	printf("Función real: %i\n", atoi(str));
	printf("FT_ATOI; %i\n", ft_atoi(str1));
	printf("Función real: %i\n", atoi(str1));
	printf("FT_ATOI; %i\n", ft_atoi(str2));
	printf("Función real: %i\n", atoi(str2));
	printf("FT_ATOI; %i\n", ft_atoi(str3));
	printf("Función real: %i\n", atoi(str3));
	printf("FT_ATOI; %i\n", ft_atoi(str4));
	printf("Función real: %i\n", atoi(str4));
	printf("FT_ATOI; %i\n", ft_atoi(str5));
	printf("Función real: %i\n", atoi(str5));
} */

/*Si primer caracter es letra, devuelve 0, si encuentra número,
representa números hasta el primer caracter no numérico.
Si los primeros caracteres son espacios, se los salta.
Si se encuentra un primer guión - , lo contempla como signo negativo*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:14:39 by antonimo          #+#    #+#             */
/*   Updated: 2024/04/18 15:38:41 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	num;

	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n == 0)
		write(fd, "0", sizeof(char));
	else if (n > 9)
	{
		num = (n % 10) + '0';
		n = n / 10;
		ft_putnbr_fd(n, fd);
		write(fd, &num, sizeof(char));
	}
	else if (n < 0)
	{
		write(fd, "-", sizeof(char));
		n = -n;
		ft_putnbr_fd(n, fd);
	}
	else
	{
		num = n + '0';
		write(fd, &num, sizeof(char));
	}
}

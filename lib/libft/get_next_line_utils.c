/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:42:24 by antonimo          #+#    #+#             */
/*   Updated: 2024/11/07 13:06:06 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_gnl(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		len;
	char	*str;
	int		i;
	int		j;

	len = (ft_strlen_gnl(s1) + ft_strlen_gnl(s2));
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[(i + j)] = '\0';
	free(s1);
	return (str);
}

int	ft_strchr_gnl(char *str, char chr)
{
	int	i;

	i = 0;
	if (chr == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == chr)
			return (1);
		i++;
	}
	return (0);
}

void	*ft_calloc_gnl(size_t size, size_t type)
{
	char	*str;
	size_t	i;

	str = (malloc(size * type));
	if (!str)
		return (NULL);
	i = 0;
	while (i < (size * type))
		str[i++] = 0;
	return (str);
}

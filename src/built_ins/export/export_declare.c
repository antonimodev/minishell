/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_declare.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:09:48 by jortiz-m          #+#    #+#             */
/*   Updated: 2025/06/03 15:35:13 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*insert_between_chr(char *str, char chr, int start, int end)
{
	char	*new_str;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	new_str = malloc((len + 3) * sizeof(char));
	if (end >= len)
		end = len + 2;
	if (end < start)
		end = start;
	while (i <= len)
	{
		if (i < len)
			new_str[j++] = str[i];
		if (i == start)
			new_str[j++] = chr;
		if (i == end)
			new_str[j++] = chr;
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	show_declare_matrix(char **declare_matrix)
{
	int		i;
	int		pos;
	char	*new_str;
	char	**matrix_copy;

	i = 0;
	matrix_copy = matrix_cpy(declare_matrix, 0);
	while (matrix_copy[i])
	{
		pos = get_chr_index(matrix_copy[i], '=');
		if (pos != (int)ft_strlen(matrix_copy[i])
			&& matrix_copy[i][pos + 1] != '"')
		{
			new_str = insert_between_chr(matrix_copy[i], '"', pos,
					ft_strlen(matrix_copy[i]) - 1);
			free(matrix_copy[i]);
			matrix_copy[i] = ft_strdup(new_str);
			free(new_str);
		}
		printf("declare -x %s\n", matrix_copy[i]);
		i++;
	}
	free_matrix(matrix_copy);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_substract.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:08:43 by jortiz-m          #+#    #+#             */
/*   Updated: 2025/05/22 11:09:05 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_utils.h"

char	**matrix_substract(char **matrix, unsigned int index)
{
	char			**new_matrix;
	unsigned int	i;
	unsigned int	j;

	new_matrix = malloc(matrix_len(matrix) * sizeof(char *));
	if (!new_matrix)
		return (NULL);
	i = 0;
	j = 0;
	while (matrix[i])
	{
		if (i != index)
		{
			new_matrix[j++] = ft_strdup(matrix[i]);
			if (!new_matrix[j - 1])
			{
				free_matrix_error(new_matrix, j);
				return (NULL);
			}
		}
		i++;
	}
	new_matrix[j] = NULL;
	free_matrix(matrix);
	return (new_matrix);
}

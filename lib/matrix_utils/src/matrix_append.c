/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:08:09 by jortiz-m          #+#    #+#             */
/*   Updated: 2025/05/22 11:08:12 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_utils.h"

char	**matrix_append(char **matrix, char *new_str)
{
	char	**new_matrix;
	int		len;

	new_matrix = matrix_cpy(matrix, 1);
	if (!new_matrix)
		return (NULL);
	len = matrix_len(matrix);
	new_matrix[len] = ft_strdup(new_str);
	if (!new_matrix[len])
	{
		free_matrix_error(new_matrix, len);
		return (NULL);
	}
	free_matrix(matrix);
	return (new_matrix);
}

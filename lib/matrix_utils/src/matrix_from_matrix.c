/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_from_matrix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:08:25 by jortiz-m          #+#    #+#             */
/*   Updated: 2025/05/22 11:08:30 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_utils.h"

char	**matrix_from_matrix(char **src_matrix, int start, int end)
{
	char	**new_matrix;
	int		len;
	int		i;

	len = end - start;
	if (len <= 0)
		return (NULL);
	new_matrix = malloc(sizeof(char *) * (len + 1));
	if (!new_matrix)
		return (NULL);
	i = 0;
	while (start < end)
	{
		new_matrix[i] = ft_strdup(src_matrix[start]);
		if (!new_matrix[i])
		{
			free_matrix_error(new_matrix, i);
			return (NULL);
		}
		i++;
		start++;
	}
	new_matrix[i] = NULL;
	return (new_matrix);
}

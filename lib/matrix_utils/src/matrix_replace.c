/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:08:37 by jortiz-m          #+#    #+#             */
/*   Updated: 2025/05/22 11:08:39 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_utils.h"

void	matrix_replace(char **matrix, int index, char *new_value)
{
	free(matrix[index]);
	matrix[index] = ft_strdup(new_value);
}

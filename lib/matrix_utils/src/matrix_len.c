/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:08:32 by jortiz-m          #+#    #+#             */
/*   Updated: 2025/05/22 11:08:34 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_utils.h"

int	matrix_len(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return (0);
	while (matrix[i])
		i++;
	return (i);
}

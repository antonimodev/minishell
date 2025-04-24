/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:40:29 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/24 10:32:09 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_minishell *minishell)
{
	int		i;
	int		j;
	bool	flag;

	i = 1;
	j = 1;
	flag = false;
	print_minishell(minishell);
	while (minishell->input_matrix[i]
		&& !ft_strcmp(minishell->input_matrix[i], "-"))
	{
		if (minishell->input_matrix[i][j] == 'n')
		{
			flag = true;
			i++;
			break;
		}
	}
	printf("Estamos aqui ahora en la matriz: %s\n", minishell->input_matrix[i]);
	printf("El valor del booleano es: %d\n", flag);
	while (minishell->input_matrix[i])
	{
		printf("%s", minishell->input_matrix[i]);
		if (minishell->input_matrix[i + 1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
}

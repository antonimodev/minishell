/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:41:27 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/03 13:41:29 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_export(t_minishell *minishell)
{
    int i;

    if (minishell->args_num > 2)
    {
        write(1, "\n", 1);
        return;
    }
    if (minishell->args_num == 2)
    {
		if (valid_symbols(minishell->input_matrix[1]))
        	minishell->envp = matrix_append(minishell->envp, minishell->input_matrix[1]);
		else
			printf("%s not a valid identifier\n", minishell->input_matrix[1]);
        return;
    }
    i = 0;
    while (minishell->envp[i])
    {
        printf("declare -x %s\n", minishell->envp[i]);
        i++;
    }
}

bool	valid_symbols(char *str)
{
	int	i;

	i = 0;
	// proteccion de si no existe str?
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:41:33 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/03 14:19:55 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_isnumber(t_minishell *minishell);

void ft_exit(t_minishell *minishell)
{
    int exit_code;
	
	exit_code = EXIT_SUCCESS;
    printf("exit\n");
    if (minishell->args_num == 1)
    {
        free_minishell(minishell);
        exit(exit_code);
    }
    if (!exit_is_number(minishell))
    {
        printf("minishell: exit: %s: numeric argument required\n", 
               minishell->input_matrix[1]);
    }
    else if (minishell->args_num > 2)
    {
        printf("minishell: exit: too many arguments\n");
        return;
    }
    else
        exit_code = ft_atoi(minishell->input_matrix[1]);
    if (minishell->envp)
        free_matrix(minishell->envp);
    free_minishell(minishell);
    exit(exit_code);
}

static bool	exit_is_number(t_minishell *minishell)
{
	int	i;

	i = 0;
	if (minishell->args_num == 2)
	{
		while (minishell->input_matrix[1][i])
		{
			if (!ft_isdigit(minishell->input_matrix[1][i]))
				return (false);
			i++;
		}	
	}
	return (true);
}

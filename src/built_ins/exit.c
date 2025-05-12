/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:41:33 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/11 14:26:34 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	exit_is_number(t_minishell *minishell);
static void	quit(t_minishell *minishell, int exit_code);

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

void	quit(t_minishell *minishell, int exit_code)
{
	if (minishell->first_cmd == 0)
	{
		printf("exit\n");
		if (minishell->envp)
			free_matrix(minishell->envp);
		free_minishell(minishell);
		exit(exit_code);
	}
}

void	ft_exit(t_minishell *minishell)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (minishell->args_num > 1)
	{
		if (!exit_is_number(minishell))
		{
			printf("minishell: exit: %s: numeric argument required\n",
				minishell->input_matrix[1]);
			minishell->exit_status = 2;
			exit_code = 2;
		}
		else if (minishell->args_num > 2)
		{
			printf("minishell: exit: too many arguments\n");
			minishell->exit_status = 1;
			exit_code = 2;
		}
		else
			exit_code = ft_atoi(minishell->input_matrix[1]);
	}
	if (exit_code > 255)
		exit_code = exit_code % 256;
	quit(minishell, exit_code);
}

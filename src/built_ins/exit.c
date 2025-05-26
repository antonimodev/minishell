/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:41:33 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/26 12:56:36 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	quit(t_minishell *minishell)
{
	if (minishell->first_cmd == 0)
	{
		printf("exit\n");
		if (minishell->envp)
			free_matrix(minishell->envp);
		if (minishell->declare_matrix)
			free_matrix(minishell->declare_matrix);
		minishell_reset_fd(minishell);
		close_write_pipes(minishell);
		close_read_pipes(minishell);
		free_minishell(minishell);
		exit(minishell->exit_status);
	}
}

void	ft_exit(t_minishell *minishell)
{
	if (minishell->args_num > 1)
	{
		if (!exit_is_number(minishell))
		{
			ft_putstr_fd("minishell: exit:", STDERR_FILENO);
			ft_putstr_fd(minishell->input_matrix[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			minishell->exit_status = 2;
		}
		else if (minishell->args_num > 2)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
			minishell->exit_status = 2;
		}
		else
			minishell->exit_status = ft_atoi(minishell->input_matrix[1]);
	}
	if (minishell->exit_status > 255)
		minishell->exit_status = minishell->exit_status % 256;
	quit(minishell);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:41:33 by antonimo          #+#    #+#             */
/*   Updated: 2025/06/03 14:07:40 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	exit_is_number(t_minishell *minishell)
{
	int	i;

	i = 1;
	if (minishell->args_num == 2)
	{
		if (minishell->input_matrix[1][0] == '-'
			|| minishell->input_matrix[1][0] == '+')
		{
			if (!ft_isdigit(minishell->input_matrix[1][1]))
				return (false);
		}
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
		close_unused_pipes(minishell);
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
			ft_putstr_fd("minishell: exit:", 2);
			ft_putstr_fd(minishell->input_matrix[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			minishell->exit_status = 2;
		}
		else if (minishell->args_num > 2)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			minishell->exit_status = 2;
		}
		else
			minishell->exit_status = ft_atoi(minishell->input_matrix[1]);
	}
	if (minishell->exit_status > 255)
		minishell->exit_status = minishell->exit_status % 256;
	quit(minishell);
}

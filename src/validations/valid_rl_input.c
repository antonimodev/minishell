/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_rl_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:43:25 by antonimo          #+#    #+#             */
/*   Updated: 2025/06/02 13:16:03 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_empty_input(t_minishell *minishell)
{
	if (minishell->user_input == NULL)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		close(minishell->fd_tools.stdin);
		close(minishell->fd_tools.stdout);
		free_matrix(minishell->envp);
		free_matrix(minishell->declare_matrix);
		free_minishell(minishell);
		exit(minishell->exit_status);
	}
	if (minishell->user_input[0] == '\0'
		|| is_empty(minishell))
		return (false);
	return (true);
}

bool	valid_rl_input(t_minishell *minishell)
{
	if (!check_empty_input(minishell))
		return (false);
	if (!check_quotes_balance(minishell->user_input))
	{
		ft_putstr_fd("minishell: syntax error: unclosed quotes\n",
			2);
		minishell->exit_status = 2;
		return (false);
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_rl_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:43:25 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/22 11:05:43 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_empty_input(t_minishell *minishell)
{
	if (minishell->user_input == NULL)
	{
		free_minishell(minishell);
		write(STDOUT_FILENO, "exit\n", 5);
		exit(EXIT_SUCCESS);
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
			STDERR_FILENO);
		return (false);
	}
	return (true);
}

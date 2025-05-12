/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_rl_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:43:25 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/11 14:04:16 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static bool	spaced_str(char *user_input)
{
	int	i;

	i = 0;
	while (user_input[i])
	{
		if (ft_isspace(user_input[i]))
			i++;
		else
			return (false);
	}
	return (true);
}
*/

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
	if (!check_empty_input(minishell)
	||	!check_quotes_balance(minishell->user_input))
		return (false);
	return (true);
}

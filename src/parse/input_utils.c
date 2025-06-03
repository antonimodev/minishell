/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:29:22 by antonimo          #+#    #+#             */
/*   Updated: 2025/06/03 15:29:24 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	valid_chr(char c)
{
	return (c != '\n' && c != '\t' && c != '\v' && c != '\f' && c != '\r');
}

bool	is_empty_quotes(char *user_input)
{
	if (ft_strlen_gnl(user_input) == 2
		&& user_input[0] == '\'' && user_input[1] == '\'')
		return (true);
	if (ft_strlen_gnl(user_input) == 2
		&& user_input[0] == '"' && user_input[1] == '"')
		return (true);
	return (false);
}

bool	is_empty(t_minishell *minishell)
{
	int		i;
	bool	is_empty_input;	

	i = 0;
	is_empty_input = false;
	if (is_empty_quotes(minishell->user_input))
		is_empty_input = true;
	else
	{
		while (minishell->user_input[i])
		{
			if (ft_isspace(minishell->user_input[i]))
				i++;
			else
				return (false);
		}
		is_empty_input = true;
	}
	if (is_empty_input)
	{
		free(minishell->user_input);
		minishell->user_input = NULL;
	}
	return (is_empty_input);
}

bool	str_equal(char *source, char *wanted)
{
	int		i;

	i = 0;
	if (ft_strlen(source) != ft_strlen(wanted))
		return (false);
	while (source[i] && wanted[i])
	{
		if (source[i] != wanted[i])
			return (false);
		i++;
	}
	return (true);
}

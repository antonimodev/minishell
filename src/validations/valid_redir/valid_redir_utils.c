/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:37:56 by jortiz-m          #+#    #+#             */
/*   Updated: 2025/05/29 13:48:09 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	redir_after_redir(char **input_matrix, int index)
{
	if ((str_equal(input_matrix[index], ">")
			|| str_equal(input_matrix[index], ">>")
			|| str_equal(input_matrix[index], "<")
			|| str_equal(input_matrix[index], "<<"))
		&& is_redirection(input_matrix[index + 1]))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(input_matrix[index + 1], 2);
		ft_putstr_fd("'\n", 2);
		return (true);
	}
	return (false);
}

bool	pipe_after_redir(char **input_matrix, int index)
{
	if (is_redirection(input_matrix[index])
		&& str_equal(input_matrix[index + 1], "|"))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (true);
	}
	return (false);
}

bool	consecutive_redirs(t_minishell *minishell)
{
	int	i;
	int	len;

	i = 0;
	len = matrix_len(minishell->input_matrix);
	while (i < len - 1)
	{
		if (is_redirection(minishell->input_matrix[i])
			&& minishell->input_matrix[i + 1])
		{
			if (redir_after_redir(minishell->input_matrix, i)
				|| pipe_after_redir(minishell->input_matrix, i))
			{
				minishell->exit_status = 2;
				minishell->redir.invalid_input = true;
				return (true);
			}
		}
		i++;
	}
	return (false);
}

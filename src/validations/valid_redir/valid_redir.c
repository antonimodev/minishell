/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:31:53 by antonimo          #+#    #+#             */
/*   Updated: 2025/06/04 13:29:40 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	redir_in_first(t_minishell *minishell)
{
	if (matrix_len(minishell->input_matrix) == 1
		&& (str_equal(minishell->input_matrix[0], "<")
			|| str_equal(minishell->input_matrix[0], "<<")
			|| str_equal(minishell->input_matrix[0], ">")
			|| str_equal(minishell->input_matrix[0], ">>")))
	{
		ft_putstr_fd("minishell: syntax error near unexpected", 2);
		ft_putstr_fd("token `newline'\n", 2);
		minishell->exit_status = 2;
		minishell->redir.invalid_input = true;
		return (true);
	}
	if (minishell->quoted_matrix[0][0] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
			2);
		minishell->exit_status = 2;
		minishell->redir.invalid_input = true;
		return (true);
	}
	return (false);
}

static bool	redir_in_last(t_minishell *minishell)
{
	int		input_matrix_len;
	int		str_len;

	input_matrix_len = matrix_len(minishell->input_matrix) - 1;
	str_len = ft_strlen(minishell->quoted_matrix[input_matrix_len]) - 1;
	if (minishell->quoted_matrix[input_matrix_len][str_len] == '>' ||
		minishell->quoted_matrix[input_matrix_len][str_len] == '<')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		ft_putstr_fd("`newline'\n", 2);
		minishell->exit_status = 2;
		minishell->redir.invalid_input = true;
		return (true);
	}
	if (minishell->quoted_matrix[input_matrix_len][str_len] == '|')
	{
		ft_putstr_fd("minishell: syntax error needs cmd after pipe\n",
			2);
		minishell->exit_status = 2;
		minishell->redir.invalid_input = true;
		return (true);
	}
	return (false);
}

bool	check_redir_existence(t_minishell *minishell)
{
	if (!ft_strchr_gnl(minishell->user_input, '|')
		&& !ft_strchr_gnl(minishell->user_input, '<')
		&& !ft_strchr_gnl(minishell->user_input, '>'))
		return (false);
	minishell->redir.redir_exist = true;
	return (true);
}

bool	check_valid_redir(t_minishell *minishell)
{
	minishell->quoted_matrix = split_with_quotes(minishell);
	minishell->input_matrix = split_without_quotes(minishell);
	process_final_matrix(minishell);
	if (redir_in_first(minishell)
		|| consecutive_redirs(minishell)
		|| redir_in_last(minishell))
		return (false);
	return (true);
}

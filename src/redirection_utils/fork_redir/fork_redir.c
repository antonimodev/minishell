/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:24:15 by antonimo          #+#    #+#             */
/*   Updated: 2025/06/04 13:24:15 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	handle_pipe_operator(t_minishell *minishell, char **matrix,
		int *operator_pos, int *i)
{
	minishell_add_redir(minishell);
	minishell->first_cmd++;
	if (process_child_cmd(minishell, matrix, operator_pos, i))
		return (true);
	return (false);
}

static void	finalize_redir(t_minishell *minishell,
		char **matrix, int operator_pos)
{
	free_matrix(minishell->input_matrix);
	minishell->input_matrix = matrix_from_matrix(matrix, operator_pos,
			matrix_len(matrix));
	free_matrix(matrix);
}

static bool	process_pipe_token(t_minishell *minishell, char **matrix,
		int *operator_pos, int *i)
{
	if (str_equal(matrix[*i], "|"))
	{
		if (handle_pipe_operator(minishell, matrix, operator_pos, i))
		{
			free_matrix(matrix);
			return (true);
		}
	}
	return (false);
}

void	handle_redir(t_minishell *minishell)
{
	int		i;
	int		operator_pos;
	char	**matrix;

	i = 0;
	operator_pos = 0;
	matrix = matrix_cpy(minishell->input_matrix, 0);
	while (matrix[i])
	{
		if (minishell->exit_status == 42)
		{
			free_matrix(matrix);
			return ;
		}
		if (minishell->redir.invalid_input)
		{
			free_matrix(matrix);
			return ;
		}
		if (process_pipe_token(minishell, matrix, &operator_pos, &i))
			return ;
		i++;
	}
	finalize_redir(minishell, matrix, operator_pos);
}

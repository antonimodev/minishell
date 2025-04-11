/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:42:25 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/11 13:42:25 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_parent_input(t_minishell *minishell)
{
	t_pipe	pipe;

	if (minishell->pipe_tools.redir_count <= 0)
		return ;
	pipe = minishell->pipe_tools.pipes[minishell->pipe_tools.redir_count - 1];
	fd_redirection(STDIN_FILENO, pipe.read_pipe);
	fd_redirection(STDOUT_FILENO, minishell->pipe_tools.STDOUT);
	close(pipe.write_pipe);
	close(pipe.read_pipe);
}

static bool	is_child_process(t_minishell *minishell, pid_t child)
{
	if (child == 0)
	{
		minishell->pid = CHILD;
		return (true);
	}
	return (false);
}

static bool	process_child_cmd(t_minishell *minishell, char **matrix,
	int *operator_pos, int current_pos)
{
	pid_t	child;

	child = fork();
	if (is_child_process(minishell, child))
	{
		minishell->input_matrix = matrix_from_matrix(matrix, *operator_pos,
				current_pos);
		return (true);
	}
	else
	{
		close(minishell->pipe_tools.pipes[minishell->pipe_tools.redir_count
			- 1].write_pipe);
		waitpid(child, NULL, 0);
	}
	*operator_pos = current_pos + 1;
	return (false);
}

void	set_redirections(t_minishell *minishell)
{
	int		i;
	int		operator_pos;
	char	**matrix;

	i = 0;
	operator_pos = 0;
	matrix = split_input(minishell);
	while (matrix[i])
	{
		if (is_redirection(matrix[i], 0))
		{
			add_redir(minishell);
			set_redir_type(minishell, matrix[i]);
			if (process_child_cmd(minishell, matrix, &operator_pos, i))
			{
				free_matrix(matrix);
				return ;
			}
		}
		i++;
	}
	set_parent_input(minishell);
	minishell->input_matrix = matrix_from_matrix(matrix, operator_pos,
			matrix_len(matrix));
	free_matrix(matrix);
}

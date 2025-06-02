/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_redir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:23:21 by jortiz-m          #+#    #+#             */
/*   Updated: 2025/06/02 14:32:25 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_child_process(t_minishell *minishell, pid_t child)
{
	if (child == 0)
	{
		minishell->pid = CHILD;
		return (true);
	}
	return (false);
}

bool	process_child_cmd(t_minishell *minishell, char **matrix,
		int *operator_pos, int *current_pos)
{
	pid_t	child;
	int		pipe_pos;

	pipe_pos = minishell->redir.redir_count - 1;
	child = fork();
	if (is_child_process(minishell, child))
	{
		set_std_signals();
		free_matrix(minishell->input_matrix);
		minishell->input_matrix = matrix_from_matrix
			(matrix, *operator_pos, *current_pos);
		return (true);
	}
	else
	{
		set_parent_signals();
		close(minishell->fd_tools.pipes[pipe_pos].write_pipe);
		get_exit_status(minishell, child);
	}
	*operator_pos = *current_pos + 1;
	return (false);
}

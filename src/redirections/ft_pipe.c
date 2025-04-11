/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:00:47 by frmarian          #+#    #+#             */
/*   Updated: 2025/04/11 14:10:37 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe(t_minishell *minishell) // rehacer funcion, es para |
{
	int cmd_position = minishell->pipe_tools.redir_count;
	int total_cmds = minishell->pipe_tools.redir_count + 1;

	if (cmd_position == 1)
	{
		t_pipe	current_pipe;
		current_pipe = minishell->pipe_tools.pipes[0];
		close(current_pipe.read_pipe);
		fd_redirection(STDOUT_FILENO, current_pipe.write_pipe);
		close(current_pipe.write_pipe);
	}
	else if (cmd_position < total_cmds)
	{
		t_pipe prev_pipe = minishell->pipe_tools.pipes[cmd_position - 2];
		t_pipe current_pipe = minishell->pipe_tools.pipes[cmd_position - 1];
		fd_redirection(STDIN_FILENO, prev_pipe.read_pipe);
		close(prev_pipe.read_pipe);
		close(current_pipe.read_pipe);
		fd_redirection(STDOUT_FILENO, current_pipe.write_pipe);
		close(current_pipe.write_pipe);
	}
}

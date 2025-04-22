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

static void close_unused_pipes(t_minishell *minishell, int cmd_position)
{
    int	i;

    i = 0;
    while (i < (cmd_position - 1))
        close(minishell->pipe_tools.pipes[i++].read_pipe);
}

void set_pipe_mode(int mode, t_pipe pipe) // cambio de nombre??
{
	if (mode == STDIN_FILENO)
	{
		close(pipe.write_pipe);
		fd_redirection(STDIN_FILENO, pipe.read_pipe);
		close(pipe.read_pipe);
	}
	else if (mode == STDOUT_FILENO)
	{
		close(pipe.read_pipe);
		fd_redirection(STDOUT_FILENO, pipe.write_pipe);
		close(pipe.write_pipe);
	}
}

void	ft_pipe(t_minishell *minishell)
{
	int		cmd_position;
	t_pipe	current_pipe;
	t_pipe	prev_pipe;

	cmd_position = minishell->pipe_tools.redir_count - 1;
	current_pipe = minishell->pipe_tools.pipes[cmd_position];
	if (!minishell->prev_redir)
		redir_first_cmd(minishell);
	else
	{
		prev_pipe = minishell->pipe_tools.pipes[cmd_position - 1];
		close_unused_pipes(minishell, cmd_position);
		set_pipe_mode(STDIN_FILENO, prev_pipe);
		set_pipe_mode(STDOUT_FILENO, current_pipe);
	}
}

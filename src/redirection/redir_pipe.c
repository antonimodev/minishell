/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:00:47 by frmarian          #+#    #+#             */
/*   Updated: 2025/05/26 14:24:07 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_read_pipes(t_minishell *minishell)
{
	int	i;

    i = 0;
    while (i < (minishell->redir.redir_count - 1))
	{
		if (minishell->fd_tools.pipes[i].read_pipe > 2)
        	close(minishell->fd_tools.pipes[i].read_pipe);
		i++;
	}
}
void	close_write_pipes(t_minishell *minishell)
{
	int	i;

    i = 0;
    while (i < (minishell->redir.redir_count - 1))
	{
		if (minishell->fd_tools.pipes[i].write_pipe > 2)
			close(minishell->fd_tools.pipes[i].write_pipe);
		i++;
	}
}

void	ft_pipe(t_minishell *minishell)
{
	int		cmd_position;
	t_pipe	current_pipe;
	t_pipe	prev_pipe;

	if (cmd_not_found(minishell))
		exit(CMD_NOT_FOUND);
	cmd_position = minishell->redir.redir_count - 1;
	current_pipe = minishell->fd_tools.pipes[cmd_position];
	prev_pipe = minishell->fd_tools.pipes[cmd_position - 1];
	set_fd_mode(STDIN_FILENO, prev_pipe);
	set_fd_mode(STDOUT_FILENO, current_pipe);
}

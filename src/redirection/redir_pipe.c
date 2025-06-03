/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:30:37 by antonimo          #+#    #+#             */
/*   Updated: 2025/06/03 15:30:39 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_read_pipes(t_minishell *minishell)
{
	int	last_pipe;

	last_pipe = minishell->redir.redir_count - 1;
	close_read_pipes(minishell);
	close(minishell->fd_tools.pipes[last_pipe].read_pipe);
}

void	close_unused_pipes(t_minishell *minishell)
{
	close_read_pipes(minishell);
	close_write_pipes(minishell);
}

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

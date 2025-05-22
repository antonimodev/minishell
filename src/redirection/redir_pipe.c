/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:00:47 by frmarian          #+#    #+#             */
/*   Updated: 2025/05/22 10:52:15 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_unused_pipes(t_minishell *minishell, int cmd_position)
{
	int	i;

	i = 0;
	while (i < (cmd_position - 1))
		close(minishell->fd_tools.pipes[i++].read_pipe);
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
	close_unused_pipes(minishell, cmd_position);
	set_fd_mode(STDIN_FILENO, prev_pipe);
	set_fd_mode(STDOUT_FILENO, current_pipe);
}

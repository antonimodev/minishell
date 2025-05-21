/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:42:51 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/21 13:50:53 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	set_fd_mode(int fd, t_pipe pipe)
{
	if (fd == STDIN_FILENO)
	{
		close(pipe.write_pipe);
		fd_redirection(STDIN_FILENO, pipe.read_pipe);
		close(pipe.read_pipe);
	}
	else if (fd == STDOUT_FILENO)
	{
		close(pipe.read_pipe);
		fd_redirection(STDOUT_FILENO, pipe.write_pipe);
		close(pipe.write_pipe);
	}
}

void	fd_redirection(int from, int to)
{
	if (dup2(to, from) == -1)
	{
		ft_putstr_fd("dup2: error duplicating fd\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	minishell_store_fd(t_minishell *minishell)
{
	minishell->fd_tools.STDIN = dup(STDIN_FILENO);
	minishell->fd_tools.STDOUT = dup(STDOUT_FILENO);
}

void	minishell_reset_fd(t_minishell *minishell)
{
	fd_redirection(STDIN_FILENO, minishell->fd_tools.STDIN);
	fd_redirection(STDOUT_FILENO, minishell->fd_tools.STDOUT);
	close(minishell->fd_tools.STDIN);
	close(minishell->fd_tools.STDOUT);
}

void	write_from_fd(int read_from, int write_into)
{
	char	buffer;

	while (read(read_from, &buffer, 1) > 0)
	{
		if (write(write_into, &buffer, 1) != 1)
		{
			ft_putstr_fd("Error al escribir en la salida estándar\n", STDERR_FILENO);
			break;
		}
	}
}

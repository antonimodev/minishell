/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:42:51 by antonimo          #+#    #+#             */
/*   Updated: 2025/06/03 12:25:44 by antonimo         ###   ########.fr       */
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
		ft_putstr_fd("dup2: error duplicating fd\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	minishell_store_fd(t_minishell *minishell)
{
	minishell->fd_tools.stdin = dup(STDIN_FILENO);
	minishell->fd_tools.stdout = dup(STDOUT_FILENO);
}

void	minishell_reset_fd(t_minishell *minishell)
{
	fd_redirection(STDIN_FILENO, minishell->fd_tools.stdin);
	fd_redirection(STDOUT_FILENO, minishell->fd_tools.stdout);
	close(minishell->fd_tools.stdin);
	close(minishell->fd_tools.stdout);
}

void	write_from_fd(int read_from, int write_into)
{
	char	buffer;

	while (read(read_from, &buffer, 1) > 0)
	{
		if (write(write_into, &buffer, 1) != 1)
		{
			ft_putstr_fd("Error al escribir en la salida estándar\n", 2);
			break ;
		}
	}
}

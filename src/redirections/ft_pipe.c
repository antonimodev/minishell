/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:00:47 by frmarian          #+#    #+#             */
/*   Updated: 2025/03/27 12:47:18 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_redirection(int from, int to)
{
    //printf("fd_redirection -> from: %d, to: %d\n", from, to);
    if (dup2(to, from) == -1)
	{
        perror("dup2: error duplicating fd");
		exit(EXIT_FAILURE);
	}
}

void ft_pipe(t_minishell *minishell)
{
	if (minishell->first_cmd == 1)
	{
		// First command writes to pipe
		fd_redirection(STDOUT_FILENO, minishell->pipe_tools.pipes[0].write_pipe);
		close(minishell->pipe_tools.pipes[0].read_pipe);
		close(minishell->pipe_tools.pipes[0].write_pipe);
	}
	/* else if (minishell->first_cmd != 1)
	{
		// Second command reads from pipe
		write(1, "holis\n", 6);
		fd_redirection(STDIN_FILENO, minishell->pipes.pipe.read_pipe);
		fd_redirection(STDOUT_FILENO, minishell->pipes.pipe.write_pipe);
		
		// Only close the write end that this process won't use
		close(minishell->pipes.pipe.write_pipe);
		close(minishell->pipes.pipe.read_pipe);
	} */
}

/*
Probablemente hagamos una funcion en la que comprobemos en handle_operator si el operador es PIPE
en el caso de que lo sea, tendremos un contador i = 0 y haremos i++, comprobar que esa i == 1, para
activar la flag minishell->first_cmd, y si es != 1, entonces se desactiva.
*/


// Contar pipes del clean input para saber cuantos segmentos guardar con create_pipe();
/* 
pipe_matrix[NUMERO DE T_PIPES][read_or_write]

fd_redirection(STDOUT_FILENO, pipe_matrix[0].write_pipe);
fd_redirection(STDOUT_FILENO, minishell->pipe.write_pipe); */
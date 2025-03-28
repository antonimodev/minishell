/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:00:47 by frmarian          #+#    #+#             */
/*   Updated: 2025/03/28 14:47:28 by frmarian         ###   ########.fr       */
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
	int		pipe_index;
	//t_pipe	current_pipe;
	//t_pipe	prev_pipe;
//
	//pipe_index = minishell->pipe_tools.pipe_count - 1;
	//current_pipe = minishell->pipe_tools.pipes[pipe_index];
	//ft_memset(&prev_pipe, 0, sizeof(t_pipe));
	if (minishell->first_cmd == 1)
	{
		fd_redirection(STDOUT_FILENO, minishell->pipe_tools.pipes[0].write_pipe);
		close(minishell->pipe_tools.pipes[0].read_pipe);
		//close(minishell->pipe_tools.pipes[0].write_pipe);
	}
	else if (minishell->first_cmd != 1)
	{
		//system("lsof -c minishell");
		//prev_pipe = minishell->pipe_tools.pipes[pipe_index - 1];
		fd_redirection(STDIN_FILENO, minishell->pipe_tools.pipes[0].read_pipe);
		fd_redirection(STDOUT_FILENO, minishell->pipe_tools.pipes[1].write_pipe);
		//close(minishell->pipe_tools.pipes[0].read_pipe);
		close(minishell->pipe_tools.pipes[0].write_pipe);
		close(minishell->pipe_tools.pipes[1].read_pipe);
		//system("lsof -c minishell");
	}
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
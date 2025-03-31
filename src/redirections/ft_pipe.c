/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:00:47 by frmarian          #+#    #+#             */
/*   Updated: 2025/03/31 12:20:26 by frmarian         ###   ########.fr       */
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
	int pipe_index = minishell->pipe_tools.pipe_count - 1;
	t_pipe current_pipe = minishell->pipe_tools.pipes[pipe_index];

	if (minishell->first_cmd == 1)
	{
		close(current_pipe.read_pipe); // cierra pipe_read
		fd_redirection(STDOUT_FILENO, current_pipe.write_pipe); // escribe en pipe 0
		close(current_pipe.write_pipe); // cierra pipe_write 0
	}
	else
	{
		t_pipe prev_pipe = minishell->pipe_tools.pipes[pipe_index - 1];

		fd_redirection(STDIN_FILENO, prev_pipe.read_pipe); // lee de pipe 0
		close(prev_pipe.read_pipe); // cierro la pipe_read
		fd_redirection(STDOUT_FILENO, current_pipe.write_pipe); // escribe en pipe1
		close(current_pipe.write_pipe); // cierro pipe_write 1
	}
}


/* void ft_pipe(t_minishell *minishell)
{
	int fd1, fd2;
	
	if (minishell->first_cmd == 1)
	{
		fd1 = open("file1.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
		fd_redirection(STDOUT_FILENO, fd1);
		close(fd1);
	}
	else if (minishell->first_cmd != 1)
	{
		fd1 = open("file1.txt", O_RDONLY);
		fd2 = open("file2.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
		fd_redirection(STDIN_FILENO, fd1);
		fd_redirection(STDOUT_FILENO, fd2);
		close(fd1);
		close(fd2);
	}
} */

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
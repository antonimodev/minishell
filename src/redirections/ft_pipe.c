/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:00:47 by frmarian          #+#    #+#             */
/*   Updated: 2025/04/09 13:45:17 by frmarian         ###   ########.fr       */
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
	// ps aux | grep root | wc -l
	// ps aux
    int cmd_position = minishell->pipe_tools.redir_count;
    int total_cmds = minishell->pipe_tools.redir_count + 1;

    // First command in the pipeline
    if (cmd_position == 1)
    {
        t_pipe		current_pipe;
		current_pipe = minishell->pipe_tools.pipes[0];

        // First command only needs to redirect stdout to the pipe's write end
        close(current_pipe.read_pipe);
        fd_redirection(STDOUT_FILENO, current_pipe.write_pipe); // 21632832
        close(current_pipe.write_pipe);
    }
    // Middle command in the pipeline
    else if (cmd_position < total_cmds)
    {
        t_pipe prev_pipe = minishell->pipe_tools.pipes[cmd_position - 2]; // Previous pipe
        t_pipe current_pipe = minishell->pipe_tools.pipes[cmd_position - 1]; // Current pipe
        // Middle command: read from previous pipe, write to current pipe
        //close(prev_pipe.write_pipe); // (6) Cierro escritura de la anterior (NO SE USA)
        fd_redirection(STDIN_FILENO, prev_pipe.read_pipe);
        close(prev_pipe.read_pipe); // (5) Cierro lectura de la anterior
        close(current_pipe.read_pipe); // (7) NO SE USA AHORA ES LA ACTUAL, LA CERRAMOS
        fd_redirection(STDOUT_FILENO, current_pipe.write_pipe); // SE REDIRECCIONA
        close(current_pipe.write_pipe); // (8)
    }
}

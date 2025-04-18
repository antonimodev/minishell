/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:10:58 by frmarian          #+#    #+#             */
/*   Updated: 2025/04/11 14:10:59 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_redir_append(t_minishell *minishell)
{
    int file;
    int prev_pipe;
    int current_pipe;

    prev_pipe = minishell->pipe_tools.redir_count - 2;
    current_pipe = minishell->pipe_tools.redir_count - 1;
    
    // El primer comando:
    if (!minishell->prev_redir)
		redir_first_cmd(minishell);
    else
	{
		if (minishell->prev_redir == PIPE) // Controla la combinacion de pipes ls | wc >> hola.txt
		{
			ft_pipe(minishell);
			return ;
		}
		// Comandos intermedios:
		file = open(minishell->input_matrix[0], O_CREAT | O_APPEND, 0644);
		if (file == -1)
		{
			perror("Error al abrir el archivo");
			return;
		}
		close(file);

		pipe_to_file(minishell->pipe_tools.pipes[prev_pipe].read_pipe, minishell->pipe_tools.pipes[current_pipe].write_pipe);
		// No sé si aquí hay que ir cerrando las pipes al igual que en ft_pipe()
		// Yo he ejecutado y funciona sin cerrarlas aquí, aún así puede ser interesante implementar
		// close_unused_pipes que la tenemos static en ft_pipe()
	}
}

void    ft_redir_append_parent(t_minishell *minishell)
{
	int		file;
    int     pipe_read;

    pipe_read = minishell->pipe_tools.pipes[minishell->pipe_tools.redir_count - 1].read_pipe;
	file = open(minishell->input_matrix[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (file == -1)
    {
        perror("Error al abrir el archivo");
        return;
    }
	pipe_to_file(pipe_read, file);
	close(file);
}
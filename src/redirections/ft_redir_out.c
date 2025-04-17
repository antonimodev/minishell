/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:11:27 by frmarian          #+#    #+#             */
/*   Updated: 2025/04/11 14:11:29 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//pipe_to_file: escribe el contenido de un pipe a un archivo
//set_pipe_mode: establece el modo de una pipe (lectura o escritura)

// Nombre provisional, la idea es crear un archivo vacio y cerrarlo
// al cerrarlo en la misma funcion no suele ser muy generica la funcion.
static void	create_empty_file(char *filename)
{
	int	file;

	file = open(filename, O_CREAT | O_TRUNC, 0644);
    if (file == -1)
    {
        perror("Error al abrir el archivo");
        return;
    }
    close(file);
}

void    ft_redir_out(t_minishell *minishell)
{
    int file;
    int prev_pipe;
    int current_pipe;

    prev_pipe = minishell->pipe_tools.redir_count - 2;
    current_pipe = minishell->pipe_tools.redir_count - 1;
    
    // El primer comando:
    if (!minishell->prev_redir)
    {
        // Simplemente configuramos la salida estándar para que vaya a la pipe actual
        set_pipe_mode(STDOUT_FILENO, minishell->pipe_tools.pipes[current_pipe]);
        return;
    }
    
	// Comandos intermedios:
    create_empty_file(minishell->input_matrix[0]);
    
    pipe_to_file(minishell->pipe_tools.pipes[prev_pipe].read_pipe, minishell->pipe_tools.pipes[current_pipe].write_pipe);
}

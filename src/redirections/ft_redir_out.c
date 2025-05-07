/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:11:27 by frmarian          #+#    #+#             */
/*   Updated: 2025/04/29 13:03:37 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//pipe_to_file: escribe el contenido de un pipe a un archivo
//set_pipe_mode: establece el modo de una pipe (lectura o escritura)

// Nombre provisional, la idea es crear un archivo vacio y cerrarlo
// al cerrarlo en la misma funcion no suele ser muy generica la funcion.
static void	create_empty_file(int *file, char *filename)
{
	*file = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (*file == -1)
    {
        perror("Error al abrir el archivo");
        return;
    }
}

/* void    ft_redir_out(t_minishell *minishell)
{
    int prev_pipe;
    int current_pipe;
    int file;

    prev_pipe = minishell->pipe_tools.redir_count - 2;
    current_pipe = minishell->pipe_tools.redir_count - 1;
    create_empty_file(&file, minishell->input_matrix[0]);
    if (minishell->redirection != REDIR_OUT)
    {
        pipe_to_file(minishell->pipe_tools.pipes[prev_pipe].read_pipe, file);
        close(file);
        return ;
    }
    pipe_to_file(minishell->pipe_tools.pipes[prev_pipe].read_pipe, minishell->pipe_tools.pipes[current_pipe].write_pipe);
    // No sé si aquí hay que ir cerrando las pipes al igual que en ft_pipe()
    // Yo he ejecutado y funciona sin cerrarlas aquí, aún así puede ser interesante implementar
    // close_unused_pipes que la tenemos static en ft_pipe()
} */

void	ft_redir_out_parent(t_minishell *minishell)
{
	int	file;
    int	current_pipe;

	current_pipe = minishell->pipe_tools.redir_count - 1;
	file = open(minishell->input_matrix[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file == -1)
    {
        perror("Error al abrir el archivo");
        return;
    }
	pipe_to_file(minishell->pipe_tools.pipes[current_pipe].read_pipe, file);
	close(file);
}


void	ft_redir_out(t_minishell *minishell, int *index) // ls | wc > perro | ls > gator
{
	int		file;

	(*index)++;
	while (minishell->input_matrix[*index])
	{
		create_empty_file(&file, minishell->input_matrix[*index]);
		if (minishell->input_matrix[(*index) + 1] == REDIR_OUT)
		{
			close(file);
			(*index) = (*index) + 2;
		}
		else
		{
			pipe_to_file(STDOUT_FILENO, file);
			close(file);
		}
	}
}

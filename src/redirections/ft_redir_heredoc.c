/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:11:21 by frmarian          #+#    #+#             */
/*   Updated: 2025/04/30 14:06:43 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// RECOGER TODO EL BLOQUE, grep "perro" << EOF > output.txt
void    ft_redir_heredoc(t_minishell *minishell) //grep "perro" << EOF
{
    /*
    - Creo una pipe temporal
    - Variable que recoje el valor de un readline
    - Readline -> para almacenar todo lo que escriba el usuario
        - Comprobar si strcmp de la variable de readline == delimitador
            Si lo es, pues rompe el bucle
    - string -> ft_putendl_fd(string, pipe_temporal.write_pipe)
    - CMD -> set_pipe_mode(STDIN_FILENO, pipe_temporal)
    - free(string) por si es buena practica ya que execve deberia de limpiar pero bueno
    - set_pipe_mode(STDOUT_FILENO, current_pipe)
    */
}

void    ft_redir_heredoc_parent(t_minishell *minishell) //grep "perro" << EOF
{
	char    *input_heredoc;
    t_pipe  temp_pipe;
    int     last_pos;
//  int     current_pipe;

	temp_pipe = create_pipe();
	last_pos = matrix_len(minishell->input_matrix) - 1;
	//current_pipe = minishell->pipe_tools.redir_count - 1; 
	input_heredoc = readline("> ");
	print_minishell(minishell);
    while (input_heredoc)
    {
		printf("input heredoc: %s\n", input_heredoc);
		free(input_heredoc);
        input_heredoc = readline("> ");
  		if (!input_heredoc)
		{
			perror("ze deberia haber zalido con el delimitadó");
			break ;
		}
        if (ft_strcmp(input_heredoc, minishell->input_matrix[last_pos]) == 0)
		{
			free(input_heredoc);
            break ;
		}
		ft_putendl_fd(input_heredoc, temp_pipe.write_pipe); // la current_pipe original viene cerrada
		free(input_heredoc);
    }
	set_pipe_mode(STDIN_FILENO, temp_pipe);
}


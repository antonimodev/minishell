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
/*void    ft_redir_heredoc(t_minishell *minishell) // wc < grep "perro" << EOF > output.txt
{
    char    *input_heredoc;

    fd_redirection(STDIN_FILENO, minishell->pipe_tools.STDIN);
}*/

void    ft_redir_heredoc_parent(t_minishell *minishell) //grep "perro" << EOF
{
	char    *input_heredoc;
    t_pipe  temp_pipe;
    int     last_pos;
//  int     current_pipe;

	temp_pipe = create_pipe();
	last_pos = matrix_len(minishell->input_matrix) - 1;
	//current_pipe = minishell->pipe_tools.redir_count - 1; 
	print_minishell(minishell);
    while (1)
    {
        input_heredoc = readline("> ");
  		if (!input_heredoc) // que ha hecho CTRL + D
		{
			printf("minishell: warning: here-document delimited by end-of-file (wanted '%s')\n",
                minishell->input_matrix[last_pos]);
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
    minishell->input_matrix = clean_matrix_redirs(minishell);
}


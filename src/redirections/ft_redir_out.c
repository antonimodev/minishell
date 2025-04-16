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

/*
    nombre del archivo que viene de input_matrix

    ls > hola.txt
*/
void    ft_redir_out(t_minishell *minishell)
{
    int file;

    if (!minishell->prev_redir) // ESTO INDICA QUE ES EL 1º COMANDO
    {
        set_pipe_mode(STDOUT_FILENO,
            minishell->pipe_tools.pipes[minishell->pipe_tools.redir_count - 1]);
        return ;
    }
    
    file = open(minishell->input_matrix[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    fd_redirection(STDOUT_FILENO, file);
}

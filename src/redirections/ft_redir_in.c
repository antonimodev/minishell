/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:10:50 by frmarian          #+#    #+#             */
/*   Updated: 2025/04/11 14:11:10 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_in(t_minishell *minishell)
{
    int		fd;
    int		last_fd;
	int		current_pipe;
    t_pipe	temp_pipe;

    //if (!check_file_in_matrix)
        //se sale completamente, escribe msj de error en pantalla y el padre vuelve a pedir el input
	current_pipe = minishell->pipe_tools.redir_count - 1;
    last_fd = matrix_len(minishell->input_matrix);
    fd = open(minishell->input_matrix[last_fd - 1], O_RDONLY);

	pipe_to_file(fd, temp_pipe.write_pipe);

	set_pipe_mode(STDIN_FILENO, temp_pipe);
	set_pipe_mode(STDOUT_FILENO, minishell->pipe_tools.pipes[current_pipe]);
}

bool   check_file_in_matrix(char **matrix)
{
    int i;

    i = 2;
    while (matrix[i])
    {
        if (access(matrix[i], F_OK | R_OK) < 0)
            return (false);
        i = i + 2;
    }
    return (true);
}

// if (minishell-redirection == REDIR_IN)
	//foo();

/* char	**foo(char **matrix, int operator_pos, int *current_pos)
{
	int		i;
	char	**new_matrix;

	i = 0;
	while (matrix[operator_pos])
	{
		if (matrix[i] != REDIR_IN)
			new_matrix = matrix_from_matrix(matrix, 0, i);
		i = i + 2;
	}
	//flag;
    *current_pos =
    return (new_matrix);
}

void    foo()
{
    while (matrix[i])
	{
		if (matrix[i] != REDIR_IN)
			minishell->redir_pos = i;
		i = i + 2;
	}
} */
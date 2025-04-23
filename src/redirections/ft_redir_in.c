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

    if (!check_file_in_matrix)
	{
		//msj de error
		free_minishell(minishell);
		exit(EXIT_FAILURE);
	}
	current_pipe = minishell->pipe_tools.redir_count - 1;
    last_fd = matrix_len(minishell->input_matrix);
    fd = open(minishell->input_matrix[last_fd - 1], O_RDONLY);

	pipe_to_file(fd, temp_pipe.write_pipe);
	close(fd);
	//set_pipe_mode(STDIN_FILENO, temp_pipe);
	fd_redirection(STDIN_FILENO, temp_pipe.read_pipe);
	if (minishell->prev_redir)
		set_pipe_mode(STDOUT_FILENO, minishell->pipe_tools.pipes[current_pipe]);
}

void	ft_redir_in_parent(t_minishell *minishell)
{
    int		fd;
    int		last_fd;
	int		current_pipe;

    if (!check_file_in_matrix)
	{
		minishell->valid_file = true;
		//mensaje de error
		return ;
	}
	current_pipe = minishell->pipe_tools.redir_count - 1;
    last_fd = matrix_len(minishell->input_matrix);
    fd = open(minishell->input_matrix[last_fd - 1], O_RDONLY);
	if (fd == -1)
    {
        perror("Error al abrir el archivo");
        return;
    }
	pipe_to_file(fd, minishell->pipe_tools.pipes[current_pipe].write_pipe);
	close(fd);
	//set_pipe_mode(STDIN_FILENO, minishell->pipe_tools.pipes[current_pipe]);
	fd_redirection(STDIN_FILENO, minishell->pipe_tools.pipes[current_pipe].read_pipe);
}

bool   check_file_in_matrix(char **matrix)
{
    int i;

	i = 0;
	while (matrix[i])
	{
		if (is_redirection)
			break ;
		i++;
	}
    while (matrix[i])
    {
		if (is_redirection(matrix[i], 0))
			i++;
        else if (access(matrix[i], F_OK | R_OK) < 0)
		{
			//msj de error
            return (false);
		}
    }
    return (true);
}

void	foo(char **matrix, int *current_pos)
{
    (*current_pos)++;
    while (matrix[*current_pos])
    {
        if (!is_redirection(matrix[*current_pos], 0))
        {
		    (*current_pos)++;
			continue ;
		}
        if (matrix[*current_pos] == '<')
			(*current_pos)++;
		else if(matrix[*current_pos] != '<')
			return ;
    }
	//flag
    return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:10:50 by frmarian          #+#    #+#             */
/*   Updated: 2025/04/29 12:14:38 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**clean_redir_in_matrix(t_minishell *minishell) // nombres...
{
	char	**new_matrix;
	int		end;

	end = 0;
	while (minishell->input_matrix[end] && minishell->input_matrix[end][0] != '<')
		end++;
	new_matrix = matrix_from_matrix(minishell->input_matrix, 0, end);
	free_matrix(minishell->input_matrix);
	return (new_matrix);
}

void	ft_redir_in(t_minishell *minishell)
{
    t_pipe	temp_pipe;
	int		current_pipe;
    int		last_fd;
    int		fd;

    if (!check_file_in_matrix(minishell->input_matrix))
	{
		free_minishell(minishell);
		exit(INVALID_FILE);
	}
	temp_pipe = create_pipe();
	current_pipe = minishell->pipe_tools.redir_count - 1;
    last_fd = matrix_len(minishell->input_matrix);
    fd = open(minishell->input_matrix[last_fd - 1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error al abrir el archivo");
		return;
	}
	pipe_to_file(fd, temp_pipe.write_pipe);
	close(fd);
	set_pipe_mode(STDIN_FILENO, temp_pipe);
	set_pipe_mode(STDOUT_FILENO, minishell->pipe_tools.pipes[current_pipe]);
	minishell->input_matrix = clean_redir_in_matrix(minishell);
}

void	ft_redir_in_parent(t_minishell *minishell)
{
    int		fd;
    int		last_fd;
	int		current_pipe;

    if (!check_file_in_matrix(minishell->input_matrix))
	{
		minishell->invalid_file = true;
		return ;
	}
	current_pipe = minishell->pipe_tools.redir_count - 1;
    last_fd = matrix_len(minishell->input_matrix) - 1;
    fd = open(minishell->input_matrix[last_fd], O_RDONLY);
	if (fd == -1)
    {
        perror("Error al abrir el archivo");
        return;
    }
	pipe_to_file(fd, minishell->pipe_tools.pipes[current_pipe].write_pipe);
	close(fd);
	set_pipe_mode(STDIN_FILENO, minishell->pipe_tools.pipes[current_pipe]);
	minishell->input_matrix = clean_redir_in_matrix(minishell);
}

bool   check_file_in_matrix(char **matrix) // comprobacion de existencia de archivos intermedios
{
    int i;

	i = 0;
	while (matrix[i] && !is_redirection(matrix[i], 0))
		i++;
    while (matrix[i])
    {
		if (is_redirection(matrix[i], 0))
			i++;
        else if (access(matrix[i], F_OK | R_OK) < 0)
		{
			perror("Error: file doesn't exist or is not readable");
            return (false);
		}
		else
			i++;
    }
    return (true);
}

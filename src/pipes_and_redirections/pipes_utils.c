/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:46:33 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/20 12:19:47 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	cmd_not_found(t_minishell *minishell)
{
	if (!minishell->cmd_path && !is_built_in(minishell))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(minishell->input_matrix[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		minishell->exit_status = CMD_NOT_FOUND;
		return (true);
	}
	return (false);
}

void	pipe_to_file(int read_from, int write_into)
{
	char	buffer;

	while (read(read_from, &buffer, 1) > 0)
	{
		if (write(write_into, &buffer, 1) != 1)
		{
			perror("Error al escribir en la salida estándar");
			break;
		}
	}
}

void	redir_first_cmd(t_minishell *minishell)
{
    int current_pipe;

	if (cmd_not_found(minishell))
		exit(CMD_NOT_FOUND);
	current_pipe = minishell->pipe_tools.redir_count - 1;
	set_pipe_mode(STDOUT_FILENO, minishell->pipe_tools.pipes[current_pipe]);
	return ;
}

void	fd_redirection(int from, int to)
{
	if (dup2(to, from) == -1)
	{
		perror("dup2: error duplicating fd");
		exit(EXIT_FAILURE);
	}
}

void	store_fd(t_minishell *minishell)
{
	minishell->pipe_tools.STDIN = dup(STDIN_FILENO);
	minishell->pipe_tools.STDOUT = dup(STDOUT_FILENO);
}

void	reset_fd(t_minishell *minishell)
{
	fd_redirection(STDIN_FILENO, minishell->pipe_tools.STDIN);
	fd_redirection(STDOUT_FILENO, minishell->pipe_tools.STDOUT);
	close(minishell->pipe_tools.STDIN);
	close(minishell->pipe_tools.STDOUT);
}

void	pipe_append(t_minishell *minishell, t_pipe *pipe)
{
	t_pipe	*tmp;
	int		i;

	i = 0;
	tmp = malloc((minishell->pipe_tools.redir_count) * sizeof(t_pipe));
	if (!tmp)
	{
		perror("pipe_append: malloc");
		return ;
	}
	while (i < minishell->pipe_tools.redir_count - 1)
	{
		tmp[i] = minishell->pipe_tools.pipes[i];
		i++;
	}
	tmp[i] = *pipe;
	if (minishell->pipe_tools.pipes)
		free(minishell->pipe_tools.pipes);
	minishell->pipe_tools.pipes = tmp;
}


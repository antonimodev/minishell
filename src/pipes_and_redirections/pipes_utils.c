/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:46:33 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/30 13:16:13 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	cmd_not_found(t_minishell *minishell)
{
	if (!minishell->cmd_path && !is_built_in(minishell))
	{
		printf("minishell: %s: command not found\n",
			minishell->input_matrix[0]);
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
	fd_redirection(STDOUT_FILENO, minishell->pipe_tools.STDOUT); // para resetear la salida ya que si sale con "ls > file" el stdout
	//se quedaba en file, ya que esto lo hacia antes un hijo pero ahora lo hace el padre
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
		perror("malloc");
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


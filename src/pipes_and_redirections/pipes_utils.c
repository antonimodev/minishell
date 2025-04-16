/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:46:33 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/11 14:10:33 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ls > hola.txt
/* static void	foo(t_minishell *minishell, int pipe_fd)
{
	int		file;
	char	c;

	file = open(minishell->input_matrix[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file == -1)
    {
        perror("Error al abrir el archivo");
        return;
    }
	while (read(pipe_fd, &c, 1) > 0)
	{
		if (write(file, &c, 1) != 1)
		{
			perror("Error al escribir en la salida estándar");
			break;
		}
	}
	close(file);
} */

static void ft_redir_out_parent(t_minishell *minishell)
{
    int     pipe_read;
	int		file;
	char	c;

    pipe_read = minishell->pipe_tools.pipes[minishell->pipe_tools.redir_count - 1].read_pipe;
	file = open(minishell->input_matrix[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file == -1)
    {
        perror("Error al abrir el archivo");
        return;
    }
	while (read(pipe_read, &c, 1) > 0)
	{
		if (write(file, &c, 1) != 1)
		{
			perror("Error al escribir en la salida estándar");
			break;
		}
	}
	close(file);
}

void    redirect(t_minishell *minishell)
{
    if (minishell->pid == CHILD)
        redirect_child(minishell);
    else if (minishell->redirection != PIPE)
        redirect_parent(minishell);
}

void	redirect_child(t_minishell *minishell)
{
	if (minishell->redirection == PIPE)
		ft_pipe(minishell);
	else if (minishell->redirection == REDIR_OUT)
		ft_redir_out(minishell);
	/* 	else if (minishell->redirection == REDIR_IN)
			ft_redir_in();
		else if (minishell->redirection == REDIR_APPEND)
				ft_redir_append(minishell);
		else if (minishell->redirection == REDIR_HEREDOC)
			ft_redir_heredoc(); */
}

void	redirect_parent(t_minishell *minishell)
{
	if (minishell->redirection == PIPE)
		set_pipe_mode(STDIN_FILENO, minishell->pipe_tools.pipes[minishell->pipe_tools.redir_count - 1]);
	else if (minishell->redirection == REDIR_OUT) // >
		ft_redir_out_parent(minishell);
	/* 	else if (minishell->redirection == REDIR_IN)
			ft_redir_in();
		else if (minishell->redirection == REDIR_APPEND)
				ft_redir_append(minishell);
		else if (minishell->redirection == REDIR_HEREDOC)
			ft_redir_heredoc(); */
}

/* void	redirect(t_minishell *minishell)    ESTE ES EL ORIGINAL
{
	if (minishell->redirection == PIPE)
		ft_pipe(minishell);
	else if (minishell->redirection == REDIR_OUT)
		ft_redir_out(minishell);
	/* 	else if (minishell->redirection == REDIR_IN)
			ft_redir_in();
		else if (minishell->redirection == REDIR_APPEND)
				ft_redir_append(minishell);
		else if (minishell->redirection == REDIR_HEREDOC)
			ft_redir_heredoc();
} */

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
	if (minishell->redirection)
	{
		fd_redirection(STDIN_FILENO, minishell->pipe_tools.STDIN);
		close(minishell->pipe_tools.STDIN);
		close(minishell->pipe_tools.STDOUT);
	}
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

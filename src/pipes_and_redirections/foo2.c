/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:50:03 by frmarian          #+#    #+#             */
/*   Updated: 2025/03/20 12:50:03 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool check_redirection(t_minishell *minishell);
//static bool	check_redir_existence(t_minishell *minishell);
//static bool check_valid_redir(t_minishell *minishell);
static void set_redir_type(t_minishell *minishell, char *str);
static bool process_child_cmd(t_minishell *minishell, char **matrix, 
	int *operator_pos, int current_pos);
static bool is_child_process(t_minishell *minishell, pid_t child);
static void	set_parent_input(t_minishell *minishell);
static void	pipe_append(t_minishell *minishell, t_pipe *pipe);
static void	add_redir(t_minishell *minishell);

static bool is_child_process(t_minishell *minishell, pid_t child)
{
	if (child == 0)
	{
		minishell->pid = CHILD;
		return (true);
	}
	return (false);
}

void	set_redirections(t_minishell *minishell)
{
	int		i;
	int		operator_pos;
	char	**matrix;

	i = 0;
	operator_pos = 0;
	matrix = split_input(minishell);
	while (matrix[i])
	{
		if (is_redirection(matrix[i], 0))
		{
			minishell->pipe_tools.redir_count++;
			add_redir(minishell); // append a array de pipes
			set_redir_type(minishell, matrix[i]);
			if (process_child_cmd(minishell, matrix, &operator_pos, i))
			{
				free_matrix(matrix);
				return ;
			}
		}
		i++;
	}
	set_parent_input(minishell);
	minishell->input_matrix = matrix_from_matrix(matrix, operator_pos, matrix_len(matrix));
	free_matrix(matrix);
}

static bool process_child_cmd(t_minishell *minishell, char **matrix, 
	int *operator_pos, int current_pos)
{
	pid_t child;

	child = fork();
	if (is_child_process(minishell, child))
	{
		minishell->input_matrix = matrix_from_matrix(matrix, *operator_pos, current_pos);
		return (true);
	}
	else
	{
		close(minishell->pipe_tools.pipes[minishell->pipe_tools.redir_count - 1].write_pipe);
		waitpid(child, NULL, 0);
	}
	*operator_pos = current_pos + 1;
	return (false);
}

bool	check_redir_existence(t_minishell *minishell)
{
	if (!ft_strchr_gnl(minishell->user_input, '|')
	&&	!ft_strchr_gnl(minishell->user_input, '<')
	&&	!ft_strchr_gnl(minishell->user_input, '>'))
		return (false);
	return (true);
}

bool check_valid_redir(t_minishell *minishell)
{
	if (is_redirection(minishell->user_input, 0) ||
		is_redirection(minishell->user_input, 
		ft_strlen(minishell->user_input) - 1))
		return (false);
	return (true);
}

static void set_redir_type(t_minishell *minishell, char *str)
{
    if (!str || !str[0])
        minishell->redirection = NONE;
    else if (str[0] == '|' && !str[1])
        minishell->redirection = PIPE;
    else if (str[0] == '<' && !str[1])
        minishell->redirection = REDIR_IN;
    else if (str[0] == '>' && !str[1])
        minishell->redirection = REDIR_OUT;
    else if (str[0] == '>' && str[1] == '>' && !str[2])
        minishell->redirection = REDIR_APPEND;
    else if (str[0] == '<' && str[1] == '<' && !str[2])
        minishell->redirection = REDIR_HEREDOC;
}

// ls -la|grep data

/*
COMANDO > ARCHIVO     # Escribe la salida en un archivo (sobrescribe)

COMANDO >> ARCHIVO    # Agrega la salida al final del archivo (sin borrar)

COMANDO < ARCHIVO     # Usa un archivo como entrada en lugar del teclado

COMANDO | COMANDO2    # Usa la salida de un comando como entrada de otro
{
	ls | grep "lo que sea"
	ls -la | grep "lo que sea"
	ls -la | cat -e
}

COMANDO 2> ERROR.LOG  # Guarda los errores en un archivo
COMANDO > SALIDA 2>&1 # Guarda salida + errores en un archivo

COMANDO << FIN        # Escribe varias líneas hasta encontrar "FIN"

<< SIGNIFICA HEREDOC

*/

static void	add_redir(t_minishell *minishell)
{
	t_pipe	pipe;

	pipe = create_pipe();
	pipe_append(minishell, &pipe);
}

static void	pipe_append(t_minishell *minishell, t_pipe *pipe)
{
	t_pipe	*tmp;
	int		i;

	i = 0;
	tmp = malloc((minishell->pipe_tools.redir_count) * sizeof(t_pipe));
	if (!tmp)
	{
		perror("malloc");
		return;
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

static void set_parent_input(t_minishell *minishell)
{
	t_pipe pipe;

	if (minishell->pipe_tools.redir_count <= 0)
		return;

	pipe = minishell->pipe_tools.pipes[minishell->pipe_tools.redir_count - 1];
	fd_redirection(STDIN_FILENO, pipe.read_pipe);
	fd_redirection(STDOUT_FILENO, minishell->pipe_tools.STDOUT); //el padre siempre mira al STDOUT

	close(pipe.write_pipe);
	close(pipe.read_pipe);
}
/* 	t_pipe pipe;

	if (minishell->pipe_tools.redir_count <= 0)
		return;
	pipe = minishell->pipe_tools.pipes[minishell->pipe_tools.redir_count - 1];
	fd_redirection(STDIN_FILENO, pipe.read_pipe);
	fd_redirection(STDOUT_FILENO, minishell->pipe_tools.STDOUT);
	close(pipe.write_pipe);
	close(pipe.read_pipe); 
}*/

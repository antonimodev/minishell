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
static bool	check_redir_existence(t_minishell *minishell);
static bool check_valid_redir(t_minishell *minishell);
static void set_operator_type(t_minishell *minishell, char *str);
static bool handle_operator(t_minishell *minishell, char **matrix, 
	int *operator_pos, int current_pos);
static bool is_child_process(t_minishell *minishell, pid_t child);
static void	set_parent_input(t_minishell *minishell);
static void	pipe_append(t_minishell *minishell, t_pipe *pipe);
static void	count_redir(t_minishell *minishell);

static bool is_child_process(t_minishell *minishell, pid_t child)
{
/* 	if (child == -1)
		perror("minishell: error creating fork"); */
	if (child == 0)
	{
		//minishell->pipe = create_pipe(); Lo hemos puesto fuera, ya que pipex lo crea fuera para que compartan las pipes
		minishell->pid = CHILD;
		return (true);
	}
	return (false);
}

void	set_pipes_or_redirection(t_minishell *minishell)
{
	int		i;
	int		operator;
	char	**matrix;

	i = 0;
	operator = 0;
	if (!check_redirection(minishell))
		return ;
	matrix = ft_split(minishell->user_input, ' ');
	while (matrix[i])
	{
		if (is_redirection(matrix[i], 0))
		{
			count_redir(minishell);
			if (handle_operator(minishell, matrix, &operator, i))
			{
				free_matrix(matrix);
				return ;
			}
		}
		i++;
	}
	set_parent_input(minishell);
	minishell->input_matrix = matrix_from_matrix(matrix, operator, matrix_len(matrix));
	free_matrix(matrix);
}

static bool handle_operator(t_minishell *minishell, char **matrix, 
	int *operator_pos, int current_pos)
{
	pid_t child;
	char **cmd;

	set_operator_type(minishell, matrix[current_pos]);
	cmd = matrix_from_matrix(matrix, *operator_pos, current_pos);
	*operator_pos = current_pos + 1;

	minishell->first_cmd++;
	child = fork();
	if (is_child_process(minishell, child))
	{
		minishell->input_matrix = cmd;
		return (true);
	}
	else
		waitpid(child, NULL, 0);
	minishell->first_cmd++;
	free_matrix(cmd);
	return (false);
}

static bool check_redirection(t_minishell *minishell)
{
	if (!check_redir_existence(minishell))
	{
		minishell->input_matrix = split_input(minishell);
		return (false);
	}
	minishell->user_input = expand_pipe(minishell); // ls -la | grep data
	if (!check_valid_redir(minishell))
	{
		minishell->input_matrix = split_input(minishell);
		return (false);
	}
	return (true);
}

static bool	check_redir_existence(t_minishell *minishell)
{
	if (!ft_strchr_gnl(minishell->user_input, '|')
	&&	!ft_strchr_gnl(minishell->user_input, '<')
	&&	!ft_strchr_gnl(minishell->user_input, '>'))
		return (false);
	return (true);
}

static bool check_valid_redir(t_minishell *minishell)
{
	if (is_redirection(minishell->user_input, 0) ||
		is_redirection(minishell->user_input, 
		ft_strlen(minishell->user_input) - 1))
	{
		printf("spabila\n"); // mensaje de que la pipe no es válida ya que esta en pos 0 o len
		return (false);
	}
	return (true);
}

static void set_operator_type(t_minishell *minishell, char *str)
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

static void	count_redir(t_minishell *minishell)
{
	t_pipe	pipe;

	minishell->pipe_tools.pipe_count++;
	pipe = create_pipe();
	pipe_append(minishell, &pipe);
}

static void	pipe_append(t_minishell *minishell, t_pipe *pipe)
{
	t_pipe	*tmp;
	int		i;

	i = 0;
	tmp = malloc((minishell->pipe_tools.pipe_count) * sizeof(t_pipe));
	if (!tmp)
	{
		perror("malloc");
		return;
	}
	while (i < minishell->pipe_tools.pipe_count - 1)
	{
		tmp[i] = minishell->pipe_tools.pipes[i];
		i++;
	}
	tmp[i] = *pipe;
	if (minishell->pipe_tools.pipes)
		free(minishell->pipe_tools.pipes);
	minishell->pipe_tools.pipes = tmp;
}

static void	set_parent_input(t_minishell *minishell)
{
	t_pipe pipe;

	if (minishell->pipe_tools.pipe_count <= 0)
		return;
	pipe = minishell->pipe_tools.pipes[minishell->pipe_tools.pipe_count - 1];
	fd_redirection(STDIN_FILENO, pipe.read_pipe);
	fd_redirection(STDOUT_FILENO, minishell->pipe_tools.STDOUT);
	close(pipe.write_pipe);
	close(pipe.read_pipe);
}

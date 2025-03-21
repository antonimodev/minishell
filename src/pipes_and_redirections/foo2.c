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
//static bool	check_pipes_or_redirection(char **matrix);

static bool is_child_process(t_minishell *minishell, pid_t child)
{
/* 	if (child == -1)
		perror("minishell: error creating fork"); */
	if (child == 0)
	{
		minishell->pipe = create_pipe();
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
		if (is_pipe_or_redirection_at_pos(matrix[i], 0))
		{
			if (handle_operator(minishell, matrix, &operator, i))
			{
				free_matrix(matrix);
				return;
			}
		}
		i++;
	}
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
	*operator_pos = current_pos;

	child = fork();
	if (is_child_process(minishell, child))
	{
		minishell->input_matrix = cmd;
		return (true);
	}

	waitpid(child, NULL, 0);
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
	minishell->user_input = expand_pipe(minishell);
	if (!check_valid_redir(minishell))
		return (false);
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
	if (is_pipe_or_redirection_at_pos(minishell->user_input, 0) ||
		is_pipe_or_redirection_at_pos(minishell->user_input, 
		ft_strlen(minishell->user_input)))
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
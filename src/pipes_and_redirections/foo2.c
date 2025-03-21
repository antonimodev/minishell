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

// ls -la|grep data -> ls -la  grep data
// | ls
static void set_operator_type(t_minishell *minishell, char *str);
static bool check_redir_input(t_minishell *minishell);
//static bool	check_pipes_or_redirection(char **matrix);

void	set_pipes_or_redirection(t_minishell *minishell)
{
	int		i;
	char	**cmd;
	pid_t	child;
	int		operator;
	char	**matrix;

	i = 0;
	operator = 0;
	if (!ft_strchr_gnl(minishell->user_input, '|')
	&&	!ft_strchr_gnl(minishell->user_input, '<')
	&&	!ft_strchr_gnl(minishell->user_input, '>'))
	{
		minishell->input_matrix = split_input(minishell);
		return ;
	}
	if (!check_redir_input(minishell))
		return ;
	matrix = ft_split(minishell->user_input, ' ');
	while (matrix[i])
	{
		if (is_pipe_or_redirection_at_pos(matrix[i], 0))
		{
			set_operator_type(minishell, matrix[i]);
			cmd = matrix_from_matrix(matrix, operator, i);
			operator = i;
			child = fork();
			if (child == 0)
			{
				minishell->pid = CHILD;
				minishell->input_matrix = cmd;
				return ;
			}
			else
				waitpid(child, NULL, 0);
		}
		i++;
	}
	minishell->input_matrix = matrix_from_matrix(matrix, operator, matrix_len(matrix));
	free_matrix(matrix);
}
// matrix[0] = ls
// matrix[1] = |
// matrix[2] = grep

/* static bool	check_pipes_or_redirection(char **matrix)
{
	int	i;
	
    i = 0;
	if (matrix[i][0] == '|'
	||	matrix[i][0] == '<'
	||	matrix[i][0] == '>')
		return (true);
        i++;
    return (false);
} */
static bool check_redir_input(t_minishell *minishell)
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
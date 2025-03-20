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

// ls -la|grep data -> ls -la | grep data
// | ls
static void set_operator_type(t_minishell *minishell, char *str);

void	set_pipes_or_redirection(t_minishell *minishell)
{
	char	*clean_input;
	char	**cmd;
	char	**matrix;
	int		i;

	i = 0;
	if (!ft_strchr_gnl(minishell->user_input, '|')
	&&	!ft_strchr_gnl(minishell->user_input, '<'))
		return ;
	minishell->user_input = expand_pipe(minishell);
	if (is_pipe_or_redirection_at_pos(minishell->user_input, 0)
	||	is_pipe_or_redirection_at_pos(minishell->user_input, ft_strlen(minishell->user_input)))
	{
		// error
	}
	matrix = ft_split(minishell->user_input, ' ');
	while (matrix[i])
	{
		if (is_pipe_or_redirection_at_pos(matrix[i], 0))
		{
			set_operator_type(minishell, matrix[i]);
			//podemos hacer fork a
			cmd = matrix_from_matrix(matrix, i);
		}
			// si hacemos fork
			// if (fork == 0)
				// return
			// minishell->cmd_path = get_path(cmd, minishell->envp);
			//se va al fork exec
			// ejecutar cmd con la redireccion
		}
		i++;
}

char	**matrix_from_matrix(char **src_matrix, int index)
{
	int		i;
	char	*str;
	char	**new_matrix;
	
	i = 0;
	str = ft_strdup("");
	while (i < index)
	{
		str = ft_strjoin_gnl(str, src_matrix[i]);
		if ((i + 1) < index)
			str = ft_strjoin_gnl(str, ' ');
	i++;
	}
	new_matrix = ft_split(str, ' ');
	free(str);
	return (new_matrix);
}

bool	check_pipes_or_redirection(char **matrix)
{
	int	i;
	
    i = 0;
	if (matrix[i][0] == '|'
	||	matrix[i][0] == '<'
	||	matrix[i][0] == '>')
		return (true);
        i++;
    return (false);
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

*/
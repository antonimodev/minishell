/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:31:53 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/11 13:36:58 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_redir_existence(t_minishell *minishell)
{
	if (!ft_strchr_gnl(minishell->user_input, '|')
		&& !ft_strchr_gnl(minishell->user_input, '<')
		&& !ft_strchr_gnl(minishell->user_input, '>'))
		return (false);
	minishell->redir_existence = true;
	return (true);
}


bool	check_valid_redir(t_minishell *minishell)
{
	char	**matrix;
	int		i;

	/*
		---- Si el input_matrix[0] empieza con redireccion, o si input_matrix[len] acaba con redireccion
		[0]. <
		[len]. >
		syntax error si es el caso de [len] (aunque con | te tira un heredoc)
		syntax error si la redireccion es |

		---- Si un redir está seguido de un caracter
		[0]. echo
		[1]. -n
		[2]. contenido
		[3]. >HOLA
		[4]. archivo.txt
		
		---- 2 redirecciones seguidas, es decir, input_matrix contiene en 1 = redireccion, 2 = redireccion
		[0]. echo
		[1]. <
		[2]. >
	
	*/

	matrix = split_input(minishell);
	print_matrix(matrix); // debug
	i = 0;
	while (matrix[i] && matrix[i + 1])
	{
		if (is_redirection(matrix[i], 0))
		{
			if (!is_redirection(matrix[i], 1) && matrix[i][1])
			{
				free_matrix(matrix);
				minishell->invalid_input = true;
				return (false);
			}
		}
		i++;
	}
	free_matrix(matrix);
	return (true);
}

void	set_redir_type(t_minishell *minishell, char *str)
{
	if (minishell->redirection)
		minishell->prev_redir = minishell->redirection;
	if (str[0] == '|' && !str[1])
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

void	add_redir(t_minishell *minishell)
{
	t_pipe	pipe;

	pipe = create_pipe();
	minishell->pipe_tools.redir_count++;
	pipe_append(minishell, &pipe);
}

/* --------- TESTING CHECK VALID REDIRS ----------- */

/**
 * Comprueba si hay redirección al final sin destino
 * Ejemplo: "echo >"
 */
static bool	check_redir_without_target(char **matrix, t_minishell *minishell)
{
	int		len;

	len = matrix_len(matrix);
	if (len > 0 && is_redirection(matrix[len - 1], 0))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		minishell->invalid_input = true;
		return (false);
	}
	return (true);
}

/**
 * Comprueba si hay un pipe al inicio de la línea
 * Ejemplo: "| echo"
 */
static bool	check_pipe_at_start(char **matrix, t_minishell *minishell)
{
    if (matrix[0] && matrix[0][0] == '|' && !matrix[0][1])
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
        minishell->invalid_input = true;
        return (false);
    }
    return (true);
}

/**
 * Comprueba dos redirecciones seguidas
 * Ejemplo: "echo < >"
 */
static bool	check_consecutive_redirs(char **matrix, int i, t_minishell *minishell)
{
	if (is_redirection(matrix[i], 0) && matrix[i + 1] && is_redirection(matrix[i + 1], 0))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(matrix[i + 1], 2);
		ft_putstr_fd("'\n", 2);
		minishell->invalid_input = true;
		return (false);
	}
	return (true);
}

/**
 * Comprueba si una redirección tiene caracteres pegados
 * Ejemplo: ">archivo" en lugar de "> archivo"
 */
static bool check_redir_format(char *str, t_minishell *minishell)
{
    if (is_redirection(str, 0) && !is_redirection(str, 1) && str[1])
    {
        ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
        minishell->invalid_input = true;
        return (false);
    }
    return (true);
}

/**
 * Función principal para verificar la validez de las redirecciones
 */
bool	check_valid_redir(t_minishell *minishell)
{
	char	**matrix;
	int		i;
	bool	valid;

	matrix = split_input(minishell);
	if (!matrix || !matrix[0])
	{
		free_matrix(matrix);
		return (true);
	}
	if (!check_redir_without_target(matrix, minishell) ||
		!check_pipe_at_start(matrix, minishell))
	{
		free_matrix(matrix);
		return (false);
	}
	i = 0;
	valid = true;
	while (matrix[i] && valid)
	{
		if (!check_redir_format(matrix[i], minishell) ||
			(matrix[i + 1] && !check_consecutive_redirs(matrix, i, minishell)))
			valid = false;
		i++;
	}
	free_matrix(matrix);
	return (valid);
}

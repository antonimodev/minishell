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

static bool redir_in_first(t_minishell *minishell);
static bool consecutive_redirs(t_minishell *minishell);
static bool redir_in_last(t_minishell *minishell);

bool	check_redir_existence(t_minishell *minishell)
{
	if (!ft_strchr_gnl(minishell->user_input, '|')
		&& !ft_strchr_gnl(minishell->user_input, '<')
		&& !ft_strchr_gnl(minishell->user_input, '>'))
		return (false);
	minishell->redir_existence = true;
	return (true);
}

/*
Lista de excepciones con echo + redirecciones:

✅ [1] EJEMPLO: echo >hola
- BASH: Crea el archivo "hola" y lo deja vacío.
- MINISHELL: Crea el archivo "hola" y lo deja vacío.

✅ [2] EJEMPLO: echo ">hola"
- BASH: Imprime ">hola" en la salida estándar.
- MINISHELL: No imprime nada.

✅ [3] EJEMPLO: echo "hola >"
- BASH: Imprime "hola >" en la salida estándar.
- MINISHELL: Imprime "hola >" en la salida estándar.

✅ [4] EJEMPLO: echo "hola >" > archivo
- BASH: Crea el archivo "archivo" y le introduce "hola >".
- MINISHELL: Crea el archivo "archivo" y le introduce "hola >".

✅ [5] EJEMPLO: echo hola>
- BASH: bash: syntax error near unexpected token `newline'
- MINISHELL: minishell: syntax error near unexpected token `newline'

✅ [6] EJEMPLO: echo |jeje
- BASH: bash: jeje: command not found
- MINISHELL: minishell: jeje: command not found

✅ [7] EJEMPLO: echo "ho > la" | wc
- BASH: Devuelve 1 3 8, resultado de wc.
- MINISHELL: Devuelve 1 3 8, resultado de wc.

✅ [8] EJEMPLO: echo hola < TODO.txt
- BASH: Imprime "hola" en la salida estándar.
- MINISHELL: Imprime "hola" en la salida estándar.

✅ [9] EJEMPLO: echo hola << jeje
- BASH: Imprime "hola" en la salida estándar.
- MINISHELL: Imprime "hola" en la salida estándar.

✅ [10] EJEMPLO: echo ">" (también ">>", "<<" y "<")
- BASH: Imprime > en la salida estándar.
- MINISHELL: Imprime ">" en la salida estándar.

✅ [11] EJEMPLO: echo "|"
- BASH: Imprime | en la salida estándar.
- MINISHELL: Imprime | en la salida estándar.

✅ [12] EJEMPLO: echo <
- BASH: bash: syntax error near unexpected token `newline'
- MINISHELL: minishell: syntax error near unexpected token `newline'

✅ [13] EJEMPLO: echo >
- BASH: bash: syntax error near unexpected token `newline'
- MINISHELL: minishell: syntax error near unexpected token `newline'

✅ [14] EJEMPLO: echo |
- BASH: Abre un heredoc
- MINISHELL: minishell: syntax error cmd after pipe


mini output = ("aspas ->'")
bash output = (aspas ->')
Test  10: ❌ echo "aspas -> ' " 
mini output = ("aspas -> ' ")
bash output = (aspas -> ' )
Test  11: ❌ echo 'aspas ->"' 
mini output = ('aspas ->"')
bash output = (aspas ->")
Test  12: ❌ echo 'aspas -> " ' 
mini output = ('aspas -> " ')
bash output = (aspas -> " )
*/

bool	check_valid_redir(t_minishell *minishell)
{
	minishell->matrix_sucia = foo_split(minishell);
	minishell->input_matrix = split_input(minishell);
	dirty_to_clean(minishell, minishell->matrix_sucia);

	if (redir_in_first(minishell) || 
		consecutive_redirs(minishell) ||
		redir_in_last(minishell))
		return (false);
	return (true);
}

static bool consecutive_redirs(t_minishell *minishell)
{
	int i;

	i = 0;
	while(minishell->input_matrix[i])
	{
		if (new_is_redirection(minishell->input_matrix[i]) &&
			new_is_redirection(minishell->input_matrix[i + 1]))
		{
			printf("minishell: syntax error near unexpected token `%s'\n",
				minishell->input_matrix[i + 1]);
			minishell->invalid_input = true;
			return (true);
		}
		i++;
	}
	return (false);
}

static bool redir_in_first(t_minishell *minishell)
{
	if (minishell->matrix_sucia[0][0] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		minishell->invalid_input = true;
		return (true);
	}
	return (false);
}

static bool redir_in_last(t_minishell *minishell)
{
	int		len;
	int		len2;

	len = matrix_len(minishell->input_matrix) - 1;
	len2 = ft_strlen(minishell->matrix_sucia[len]) - 1;
	if (minishell->matrix_sucia[len][len2] == '>' ||
		minishell->matrix_sucia[len][len2] == '<')
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		minishell->invalid_input = true;
		return (true);
	}
	if (minishell->matrix_sucia[len][len2] == '|')
	{
		printf("minishell: syntax error needs cmd after pipe\n");
		minishell->invalid_input = true;
		return (true);
	}
	return (false);
}

void	add_redir(t_minishell *minishell)
{
	t_pipe	pipe;

	pipe = create_pipe();
	minishell->pipe_tools.redir_count++;
	pipe_append(minishell, &pipe);
}

/* --------- TESTING CHECK VALID REDIRS ----------- */

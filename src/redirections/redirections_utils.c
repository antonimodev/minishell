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

[5] EJEMPLO: echo hola>
- BASH: bash: syntax error near unexpected token `newline'
- MINISHELL: No imprime nada.

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

[12] EJEMPLO: echo <
- BASH: bash: syntax error near unexpected token `newline'
- MINISHELL: ==165240== Syscall param access(pathname) points to unaddressable byte(s)
==165240==    at 0x49B235B: access (access.c:27)
==165240==    by 0x10E77E: redir_in (another_test.c:164)
==165240==    by 0x10E602: process_redir (another_test.c:120)
==165240==    by 0x10E2F5: new_redirect (another_test.c:68)
==165240==    by 0x10A069: execute (exec.c:17)
==165240==    by 0x10959E: main (minishell.c:28)
==165240==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==165240== 
minishell: (null): No such file or directory

[13] EJEMPLO: echo >
- BASH: bash: syntax error near unexpected token `newline'
- MINISHELL: ==167633== Syscall param openat(filename) points to unaddressable byte(s)
==167633==    at 0x49B1F5B: open (open64.c:48)
==167633==    by 0x10E676: redir_out (another_test.c:130)
==167633==    by 0x10E5C4: process_redir (another_test.c:117)
==167633==    by 0x10E2F5: new_redirect (another_test.c:68)
==167633==    by 0x10A069: execute (exec.c:17)
==167633==    by 0x10959E: main (minishell.c:28)
==167633==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==167633== 
error al abrir en redir_out: Bad address

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
	char	**matrix;
	int		i;

 
	matrix = foo_split(minishell);
	//dirty_to_clean(minishell, matrix);
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

void	add_redir(t_minishell *minishell)
{
	t_pipe	pipe;

	pipe = create_pipe();
	minishell->pipe_tools.redir_count++;
	pipe_append(minishell, &pipe);
}

/* --------- TESTING CHECK VALID REDIRS ----------- */

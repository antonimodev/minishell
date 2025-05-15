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

[2] EJEMPLO: echo ">hola"
- BASH: Imprime ">hola" en la salida estándar.
- MINISHELL: No imprime nada.

[3] EJEMPLO: echo "hola >"
- BASH: Imprime "hola >" en la salida estándar.
- MINISHELL: No imprime nada.

[4] EJEMPLO: echo "hola >" > archivo
- BASH: Crea el archivo "archivo" y le introduce "hola >".
- MINISHELL: No crea el archivo.

[5] EJEMPLO: echo hola>
- BASH: bash: syntax error near unexpected token `newline'
- MINISHELL: No imprime nada.

✅ [6] EJEMPLO: echo |jeje
- BASH: bash: jeje: command not found
- MINISHELL: minishell: jeje: command not found

[7] EJEMPLO: echo "ho > la" | wc
- BASH: Devuelve 1 3 8, resultado de wc.
- MINISHELL: No hace nada.

✅ [8] EJEMPLO: echo hola < TODO.txt
- BASH: Imprime "hola" en la salida estándar.
- MINISHELL: Imprime "hola" en la salida estándar.

✅ [9] EJEMPLO: echo hola << jeje
- BASH: Imprime "hola" en la salida estándar.
- MINISHELL: Imprime "hola" en la salida estándar.

*/

/*bool	check_valid_redir(t_minishell *minishell)
{
	char	**matrix;
	int		i;

 
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
}*/

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

// Comprueba si una cadena contiene un operador de redirección
static bool has_redirection_char(char *str)
{
    return (ft_strchr(str, '>') || ft_strchr(str, '<') || ft_strchr(str, '|'));
}

// Verifica si es un operador de redirección válido por sí solo
static bool is_valid_operator(char *str)
{
    return ((str[0] == '>' && !str[1]) ||                   // >
            (str[0] == '<' && !str[1]) ||                   // <
            (str[0] == '|' && !str[1]) ||                   // |
            (str[0] == '>' && str[1] == '>' && !str[2]) ||  // >>
            (str[0] == '<' && str[1] == '<' && !str[2]));   // <<
}

// Verifica si hay un operador de redirección incrustado en una palabra
static bool has_embedded_operator(char *str)
{
    int i = 1; // Empezamos desde el segundo carácter
    
    if (!str || !*str)
        return false;
        
    // Verificamos si hay un carácter de redirección incrustado en el medio
    while (str[i])
    {
        if (str[i] == '>' || str[i] == '<' || str[i] == '|')
            return true;
        i++;
    }
    return false;
}

// Función principal para comprobar si las redirecciones son válidas
bool check_valid_redir(t_minishell *minishell)
{
	char **matrix;
	int i = 0;
	bool valid = true;

	matrix = split_input(minishell);
	if (!matrix)
		return false;

	//print_matrix(matrix); // debug

	// Verificamos cada token
	while (matrix[i])
	{
		// Caso 1: Si es un operador válido por sí mismo, continuamos
		if (is_valid_operator(matrix[i]))
		{
			i++;
			continue;
		}
		
		// Caso 2: Si empieza con un operador pero tiene más caracteres, es inválido
		// Ejemplo: ">file" o "|wc"
		if ((matrix[i][0] == '>' || matrix[i][0] == '<' || matrix[i][0] == '|') && matrix[i][1])
		{
			minishell->invalid_input = true;
			valid = false;
			break;
		}
		
		// Caso 3: Si contiene un operador incrustado en medio, marcamos como inválido
		// Ejemplo: "hola>file" o "cat<file"
		if (has_embedded_operator(matrix[i]))
		{
			minishell->invalid_input = true;
			valid = true; // Retornamos true para que se ejecute como echo
			break;
		}
		
		// Caso 4: Si un operador no es seguido por un argumento
		if (is_valid_operator(matrix[i]) && !matrix[i+1])
		{
			minishell->invalid_input = true;
			valid = false;
			break;
		}
		
		// Caso 5: Si hay dos operadores seguidos
		if (i > 0 && is_valid_operator(matrix[i-1]) && is_valid_operator(matrix[i]))
		{
			minishell->invalid_input = true;
			valid = false;
			break;
		}
		
		i++;
	}

	free_matrix(matrix);
	return valid;
}
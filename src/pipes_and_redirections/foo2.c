#include "minishell.h"

// ls -la|grep data -> ls -la | grep data
// | ls
/*
void set_pipes_or_redirection(t_minishell *minishell)
{
	char	*clean_input;
	
	if (ft_strchr_gnl(minishell->user_input, '|')
	||	ft_strchr_gnl(minishell->user_input, '<'))
	minishell->user_input = expand_pipe(minishell); // minishell->user_input = ls -la | grep data

	// comprobacion de index 0 y len para ver si las pipes no están ni al inicio ni al final
	// minishell->user_input = ls -la | grep data
	char	**cmd;
	char	**matrix = ft_split(minishell->user_input, ' ');
	int	i = 0;
	while (matrix[i])
	{
		if (is_pipe_or_redirection(matrix[i]))
		{
			cmd = matrix_from_matrix(matrix, i);
			// si hacemos fork, el hijo debe hacer return
			// ejecutar cmd con la redireccion
		}
		i++;
	}
}
*/

/*char	**matrix_from_matrix(char **src_matrix, int index)
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
/*
bool is_pipe_or_redirection(char *user_input)
{
	if (user_input == '|'
	||	user_input == '<'
	||	user_input == '>'
	||	ft_strncmp(user_input, ">>", 2) == 0
	||	ft_strncmp(user_input, "<<", 2) == 0)
		return (true);
	return (false);
}
*/
/*
bool	check_pipes_or_redirection(char **matrix)
{
	int	i;
	
    i = 0;
    while (matrix[i])
    {
	if (matrix[i][0] == '|'
		||	matrix[i][0] == '<'
		||	matrix[i][0] == '>'
		||	ft_strncmp(matrix[i], ">>", 2) == 0
		||	ft_strncmp(matrix[i], "<<", 2) == 0)
		return (true);
        i++;
    }
    return (false);
}
*/

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
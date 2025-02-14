#include "minishell.h"

static char	**addmatrix(char **matrix, char **word)
{
    int     i;
    int     len;
    char    **new_matrix;

	len = matrixlen(matrix);
    new_matrix = malloc(sizeof(char **) * (len + 2));
    if (!new_matrix)
        return NULL;
    i = 0;
    while (i < len)
    {
		new_matrix[i] = ft_strdup(matrix[i]);
        i++;
    }
    new_matrix[i] = ft_strdup(*word);
	new_matrix[i + 1] = NULL;
	
	free(*word);
	free_matrix(matrix);
	
	*word = ft_strdup("");
    return (new_matrix);
}

static char	*str_append_char(char *word, char c)
{
    size_t	len;
	char 	*new_str;
	
	len = ft_strlen(word);
    new_str = malloc(len + 2); // +1 for the new char and +1 for the null terminator
	len = 0;
    if (!new_str)
	return NULL;
    while (word[len])
	{
		new_str[len] = word[len];
		len++;
	}
    new_str[len] = c;
	new_str[len + 1] = '\0';
    
    free(word);
    return (new_str);
}

char **think(t_minishell *minishell)
{
	char **matrix;
	char *word;
	t_quote quote;

	matrix = malloc(sizeof(char *));
	ft_bzero(matrix, sizeof(char *));
    word = ft_strdup(""); // tiene malloc
    quote.closed = true;
    quote.type = '\0';

    int i = 0;
    while (minishell->user_input[i])
    {
        if (no_skip(minishell->user_input[i]))
        {
            if (quote.closed) // si aún no se ha abierto
            {
                if (minishell->user_input[i] == ' ') // si es espacio almacenamos el word actual
                    matrix = addmatrix(matrix, &word);
                else if (minishell->user_input[i] == '"' || minishell->user_input[i] == '\'') // si es quote
                {
                    quote.closed = false;
                    quote.type = minishell->user_input[i];
                }
                else // si minishell->user_input[i]) no es espacio ni quote, seguimos formando word
                    word = str_append_char(word, minishell->user_input[i]);
            }
            else if (minishell->user_input[i] == quote.type) // si quote esta abierto de antes y resulta que es el mismo que teniamos primero
            {
                quote.closed = true; // update to correct logic for closing quotes
                quote.type = '\0';
            }
            else // si es otro cualquier caracter y quote está abierto, concatenamos word
                word = str_append_char(word, minishell->user_input[i]);
        }
        i++;
    }
    if (word)
	{
        matrix = addmatrix(matrix, &word);
		free(word);
	}
    return (matrix);
}

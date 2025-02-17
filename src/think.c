#include "minishell.h"

static char	**addmatrix(char **matrix, char **word)
{
    int     i;
    int     len;
    char    **new_matrix;

	len = matrixlen(matrix);
    new_matrix = malloc(sizeof(char **) * (len + 2)); // + 1 por el nulo y + 1 por la nueva palabra \en caso de ser la primera iteracion, len = 0 y la primera pos para la nueva palabra y segunda para nulo
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

static char	*str_append_char(char *word, char c) // probablemente haya que mandarlo como ** para liberar
{
    size_t	len;
	char 	*new_str;
	
	len = ft_strlen(word);
    new_str = malloc(len + 2);
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
    
    free(word); // liberar
    return (new_str);
}


char **think(t_minishell *minishell)
{
	char **matrix;
	char *word;
	t_quote quote;

    if (!minishell->user_input)
        return (NULL);

	matrix = malloc(sizeof(char *));
	ft_bzero(matrix, sizeof(char *));
    word = ft_strdup("");
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
                    matrix = addmatrix(matrix, &word); // movidón de punteros, dup en copia
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
                quote.closed = true;
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

    // add makefile
    /* if (quote.close)
    {
        free_matrix(matrix);
        return (NULL);
    } */
    return (matrix);
}

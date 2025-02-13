#include "minishell.h"

static void addmatrix(t_minishell *minishell)
{
    char **new_matrix;
    int i;

    new_matrix = malloc(sizeof(char *) * (minishell->args_num + 1));
    if (!new_matrix)
        return ;

    i = 0;
    while (i < minishell->args_num) // Update to use minishell->args_num
    {
        new_matrix[i] = ft_strdup(minishell->matrix.matrix[i]);
        i++;
    }

    new_matrix[minishell->args_num] = ft_strdup(minishell->matrix.word);
    if (!new_matrix[minishell->args_num])
    {
        free(new_matrix);
        return ;
    }

    free(minishell->matrix.matrix);
	free(minishell->matrix.word);
    minishell->matrix.matrix = new_matrix;
    minishell->args_num++;
}

static void	str_append_char(t_minishell *minishell, char c)
{
    int len = ft_strlen(minishell->matrix.word);
    char *new_str = malloc(len + 2); // +1 for the new char and +1 for the null terminator
    if (!new_str)
        return;

    ft_strcpy(new_str, minishell->matrix.word);
    new_str[len] = c;
    
    free(minishell->matrix.word);
    minishell->matrix.word = new_str;
}

char **think(t_minishell *minishell)
{
    minishell->matrix.word = ft_strdup(""); // tiene malloc
    minishell->matrix.quote.closed = true;
    minishell->matrix.quote.type = '\0';

    int i = 0;
    while (minishell->user_input[i])
    {
        if (no_skip(minishell->user_input[i]))
        {
            if (minishell->matrix.quote.closed) // si aún no se ha abierto
            {
                if (minishell->user_input[i] == ' ') // si es espacio almacenamos el matrix->word actual
                    addmatrix(minishell);
                else if (minishell->user_input[i] == '"' || minishell->user_input[i] == '\'') // si es quote
                {
                    if (minishell->matrix.quote.type) // si se habia asignado un quote ya
                    {
                        if (minishell->user_input[i] == minishell->matrix.quote.type) // si es el mismo quote que teniamos, almacenamos ese tramo
                        {
                            addmatrix(minishell);
                            minishell->matrix.quote.closed = false;
                            minishell->matrix.quote.type = '\0';
                        }
                        else // si no es el mismo tipo de quote que teniamos, seguimos concatenando en word
                            str_append_char(minishell, minishell->user_input[i]);
                    }
                    else
                    {
                        minishell->matrix.quote.closed = false;
                        minishell->matrix.quote.type = minishell->user_input[i];
                    }
                }
                else // si minishell->user_input[i]) no es espacio ni quote, seguimos formando word
                    str_append_char(minishell, minishell->user_input[i]);
            }
            else if (minishell->user_input[i] == minishell->matrix.quote.type) // si quote esta abierto de antes y resulta que es el mismo que teniamos primero
            {
                minishell->matrix.quote.closed = true; // update to correct logic for closing quotes
                minishell->matrix.quote.type = '\0';
            }
            else // si es otro cualquier caracter y quote está abierto, concatenamos word
                str_append_char(minishell, minishell->user_input[i]);
        }
        i++;
    }
    if (minishell->matrix.word)
        addmatrix(minishell);
	//print_matrix(minishell->matrix.matrix);
    return minishell->matrix.matrix;
}
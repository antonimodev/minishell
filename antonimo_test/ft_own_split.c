// Si detecto una " o ' abierta, tengo que empezar a contar los caracteres \
que hay hasta que se cierre para poder hacer un malloc de la longitud exacta \
antes de esto debo saber cuántas palabras hay para hacer un malloc de la \
longitud exacta de la matriz de palabras

#include "minishell.h"

void    spaced_word(char *user_input, int *i)
{
    while (user_input[*i] && user_input[*i] == ' ') // si es espacio, avanzamos
        (*i)++;
    while (user_input[*i] && user_input[*i] != ' ') // pasamos por la palabra
    {
        if (user_input[*])
        (*i)++;
}

// Aqui entra cuando la ft anterior ha detectado que user_input[i] está en una quote \
y se encarga de retornar true en caso de que haya encontrado el cierre de la quote

bool    quoted_word(char *user_input, int *i, t_quotes *quotes)
{
    (*i)++;
    while (user_input[*i])
    {
        if (user_input[*i] == quotes->quote_type)
        {
            quotes->close = true;
            return (true);
        }
        (*i)++;
    }
    return (false);
}

int count_words(char *user_input) // l"s"
{
    int     i;
    //int   words;
    i = 0;
    while (user_input[i])
    {
        if (user_input[i] == '"' || user_input[i] == '\'')
        {
            if (!quoted_word(user_input, &i, quotes))
                return (NULL); // Error, no se cerró la comilla
            // words++; porque se cerró la comilla
            // quote_type = '\0'; // Reseteamos el tipo de comilla
            // close = false; // Reseteamos el estado de la comilla
        }
        if (user_input[i] == ' ') //
        {
            // ft
        }
        i++;
    }
}


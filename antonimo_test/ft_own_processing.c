#include "minishell.h"
// Procesar

// Inicializarla en algún lugar antes de usarla
typedef struct t_quotes
{
    bool    *close;
    char    *quote_type;
} t_quotes;

bool    foo(char chr, t_quotes *quotes)
{
    if (chr == '"' || chr == '\'')
    {
        quotes->close = false; // Se abrió una comilla
        quotes->quote_type = quote; // Guardamos el tipo de comilla
    }
}

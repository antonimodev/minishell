#include "minishell.h"

bool valid_symbols(char *str)
{
    int i;
    
    if (!str || !*str)
        return (false);
        
    // Verificar primer carácter (no puede ser un número)
    if (ft_isdigit(str[0]))
        return (false);
        
    i = 0;
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (false);
        i++;
    }
    return (true);
}
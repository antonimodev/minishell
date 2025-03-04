#include "minishell.h"

bool	valid_symbols(char *str)
{
	int	i;

	i = 0;
	// proteccion de si no existe str?
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
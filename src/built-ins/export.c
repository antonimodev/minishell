#include "minishell.h"

void ft_export(t_minishell *minishell)
{
    int i;

    if (minishell->args_num > 2)
    {
        write(1, "\n", 1);
        return;
    }
    if (minishell->args_num == 2)
    {
		if (valid_symbols(minishell->input_matrix[1]))
        	minishell->envp = matrix_append(minishell->envp, minishell->input_matrix[1]);
		else
			printf("%s not a valid identifier\n", minishell->input_matrix[1]);
        return;
    }
    i = 0;
    while (minishell->envp[i])
    {
        printf("declare -x %s\n", minishell->envp[i]);
        i++;
    }
}

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

char	**matrix_append(char **matrix, char *new_str)
{
	char	**new_matrix;
	int		len;
	
	new_matrix = matrix_cpy(matrix, 1);
	if (!new_matrix)
		return (NULL);
	len = matrixlen(matrix);
	new_matrix[len] = ft_strdup(new_str);
	if (!new_matrix[len])
	{
		free_matrix_error(new_matrix, len);
		return (NULL);
	}
	free_matrix(matrix);
	return (new_matrix);
}

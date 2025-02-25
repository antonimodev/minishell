#include "minishell.h"

char	**matrix_substract(char **matrix, unsigned int index)
{
	char			**new_matrix;
	unsigned int	i;
	unsigned int	j;

	new_matrix = malloc(matrixlen(matrix) * sizeof(char *));
	if (!new_matrix)
		return (NULL);
	i = 0;
	j = 0;
	while (matrix[i])
	{
		if (i != index)
		{
			new_matrix[j++] = ft_strdup(matrix[i]);
			if (!new_matrix[j - 1])
			{
				free_matrix_error(new_matrix, j);
				return (NULL);
			}
		}
		i++;
	}
	new_matrix[j] = NULL; // por lo visto para punteros es mas adecuado (es una matriz)
	free_matrix(matrix);
	return (new_matrix);
}

void ft_unset(t_minishell *minishell)
{
    unsigned int i;
    int arg_index;
    int var_len;

    if (minishell->args_num <= 1)
        return ;
    arg_index = 1;
    while (arg_index < minishell->args_num)
    {
        var_len = ft_strlen(minishell->input_matrix[arg_index]);
        i = 0;
        while (minishell->envp[i])
        {
            if (ft_strncmp(minishell->envp[i], minishell->input_matrix[arg_index], var_len) == 0
                && (minishell->envp[i][var_len] == '=' || minishell->envp[i][var_len] == '\0'))
            {
                minishell->envp = matrix_substract(minishell->envp, i);
                break ;
            }
            i++;
        }
        arg_index++;
    }
}

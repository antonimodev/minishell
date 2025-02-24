#include "minishell.h"

void    ft_env(t_minishell *minishell)
{
    if (minishell->args_num > 1)
    {
        printf("This command executes without arguments\n");
        return ;
    }
    print_matrix(minishell->envp);
}

/**
 * Copy from matrix to new matrix
 * @param src Matrix to be copied
 * @param extra_slots slots to add for future appends (default: 0)
 * @returns A pointer to the new copied matrix, or NULL if memory allocation fails.
 */
char    **matrix_cpy(char **src, int extra_slots) // Puede que int deba ser unsigned para evitar negativos
{
    char    **matrix;
    int     len;
    int     i;
    
    len = matrixlen(src) + extra_slots;
    matrix = malloc((len + 1) * sizeof(char *));
    if (!matrix)
        return (NULL); // revisar este return segun a la altura a la que se implemente
    i = 0;
    while (src[i] && i < len)
    {
    	matrix[i] = ft_strdup(src[i]);
		if (!matrix[i]) // quiere decir que ha fallado el dup
		{
			free_matrix_error(matrix, i);
			return (NULL); // revisar tambien este return segun la altura
		}
        i++;
    }
    while (i <= len)
        matrix[i++] = NULL;
    return (matrix);
}

void	free_matrix_error(char **matrix, int i)
{
    while (i-- > 0)
        free(matrix[i]);
    free(matrix);
}
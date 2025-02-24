#include "minishell.h"

void    ft_env(t_minishell *minishell)
{
    if (minishell->args_num > 1)
    {
        printf("This command executes without arguments\n");
        return ;
    }
    print_matrix(minishell->envp); // Habrá que hacer una copia de envp de padre a minishell->envp
    // Tener en cuenta que cuando se vaya a hacer export hay que meterlo en minishell->envpp
}

char    **matrix_cpy(char **src) // funcion para copiar las variables de entorno a mi variable de minishell
{
    char    **matrix;
    int     len;
    int     i;
    
    len = matrixlen(src);
    matrix = malloc((len + 1) * sizeof(char *));
    if (!matrix)
        return (NULL); // revisar este return segun a la altura a la que se implemente
    i = 0;
    while (i < len)
    {
    	matrix[i] = ft_strdup(src[i]);
		if (!matrix[i]) // quiere decir que ha fallado el dup
		{
			while (--i >= 0)
				free(matrix[i]);
			free (matrix);
			return (NULL); // revisar tambien este return segun la altura
		}
        i++;
    }
    matrix[i] = '\0';
    return (matrix);
}

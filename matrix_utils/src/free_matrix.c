#include "matrix_utils.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix)
	{
		while (matrix[i])
			free(matrix[i++]);
		free(matrix);
	}
}

void	free_matrix_error(char **matrix, int i)
{
    while (i-- > 0)
        free(matrix[i]);
    free(matrix);
}

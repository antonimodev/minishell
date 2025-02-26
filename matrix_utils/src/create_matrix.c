#include "matrix_utils.h"

char	**create_matrix(int n)
{
	char	**matrix;

	if (n < 0)
	{
		perror("create_matrix: Parameter must be positive");
		return (NULL);
	}
	matrix = malloc((n + 1) * sizeof(char *));
	if (!matrix)
	{
		perror("create_matrix: Error allocating matrix memory");
		return (NULL);
	}
	ft_memset(matrix, 0, (size_t)((n + 1) * sizeof(char *)));
	return (matrix);
}

#include "matrix_utils.h"

int	matrix_len(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		printf("Error: matrix_len: No existe\n");
	while (matrix[i])
		i++;
	return (i);
}

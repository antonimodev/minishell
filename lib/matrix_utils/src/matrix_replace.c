#include "matrix_utils.h"

void	matrix_replace(char **matrix, int index, char *new_value)
{
	free(matrix[index]);
	matrix[index] = ft_strdup(new_value);
}
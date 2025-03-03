#include "matrix_utils.h"

void	print_matrix(char **matrix)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (matrix[x])
	{
		y = 0;
		while (matrix[x][y])
		{
			printf("%c", matrix[x][y]);
			y++;
		}
		printf("\n");
		x++;
	}
}

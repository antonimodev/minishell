#include "matrix_utils.h"

/**
 * Copy from matrix to new matrix
 * @param src Matrix to be copied
 * @param extra_slots slots to add for future appends (default: 0)
 * @returns A pointer to the new copied matrix, or NULL if memory allocation fails.
 */
char    **matrix_cpy(char **src, int extra_slots)
{
    char    **matrix;
    int     len;
    int     i;
    
    len = matrix_len(src) + extra_slots;
    matrix = malloc((len + 1) * sizeof(char *));
    if (!matrix)
        return (NULL);
    i = 0;
    while (src[i] && i < len)
    {
    	matrix[i] = ft_strdup(src[i]);
		if (!matrix[i])
		{
			free_matrix_error(matrix, i);
			return (NULL);
		}
        i++;
    }
    while (i <= len)
        matrix[i++] = NULL;
    return (matrix);
}

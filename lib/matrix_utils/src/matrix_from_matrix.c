#include "matrix_utils.h"

char	**matrix_from_matrix(char **src_matrix, int start, int end)
{
	char	*str;
	char	**new_matrix;

	str = ft_strdup("");
	while (start < end)
	{
		str = ft_strjoin_gnl(str, src_matrix[start]);
		if ((start + 1) < end)
			str = ft_strjoin_gnl(str, " ");
		start++;
	}
	new_matrix = ft_split(str, ' ');
	free(str);
	return (new_matrix);
}

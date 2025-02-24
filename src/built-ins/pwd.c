#include "minishell.h"

void	ft_pwd(t_minishell *minishell)
{
    char	*current_dir;

	if (minishell->args_num > 1)
	{
		printf("minishell: %s: too many arguments\n", minishell->input_matrix[0]);
		return ;
	}
	current_dir = getcwd(NULL, 0);
	printf("%s", current_dir);
	free(current_dir);
}

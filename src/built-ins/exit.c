#include "minishell.h"

void	ft_exit(t_minishell *minishell)
{
	if (!ft_isnumber(minishell))
	{
		printf("minishell: exit: %s: numeric argument required\n",\
		minishell->input_matrix[1]);
		if (minishell->envp)
			free_matrix(minishell->envp);
		free_minishell(minishell);
		exit(EXIT_FAILURE);
	}
	else if (minishell->args_num > 2)
	{
		printf("minishell: %s: too many arguments\n", minishell->input_matrix[0]);
		return ;
	}
	else
	{
		// sería ético que si tiene un codigo de error valido, \
		con el codigo del primer argumento, input_matrix[1], que pa algo está.
		if (minishell->envp)
			free_matrix(minishell->envp);
		free_minishell(minishell);
		exit(EXIT_SUCCESS);
	}
}

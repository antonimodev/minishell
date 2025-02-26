#include "minishell.h"

void ft_exit(t_minishell *minishell)
{
    int exit_code;
	
	exit_code = EXIT_SUCCESS;
    printf("exit\n");
    if (minishell->args_num == 1)
    {
        free_minishell(minishell);
        exit(exit_code);
    }
    if (!ft_isnumber(minishell))
    {
        printf("minishell: exit: %s: numeric argument required\n", 
               minishell->input_matrix[1]);
    }
    else if (minishell->args_num > 2)
    {
        printf("minishell: exit: too many arguments\n");
        return;
    }
    else
        exit_code = ft_atoi(minishell->input_matrix[1]);
    if (minishell->envp)
        free_matrix(minishell->envp);
    free_minishell(minishell);
    exit(exit_code);
}

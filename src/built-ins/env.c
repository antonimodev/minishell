#include "minishell.h"

void    ft_env(t_minishell *minishell)
{
    if (minishell->args_num > 1)
    {
        printf("This command executes without arguments\n");
        return ;
    }
    print_matrix(minishell->envp);
}

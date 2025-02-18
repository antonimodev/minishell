#include "minishell.h"

void    ft_echo(t_minishell *minishell)
{
    int     i;
    bool    flag;

    i = 1;
    flag = false;
    while (minishell->input_matrix[i] && ft_strcmp(minishell->input_matrix[i], "-n") == 0)
    {
        flag = true;
        i++;
    }
    while (minishell->input_matrix[i])
    {
        printf("%s", minishell->input_matrix[i]);
        if (minishell->input_matrix[i + 1])
            printf(" ");
        i++;
    }
    if (!flag)
        printf("\n");
}
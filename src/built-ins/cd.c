#include "minishell.h"

void	ft_cd(t_minishell *minishell)
{
	struct stat	buffer;
    const char	*cmd;
    const char	*arg;
	
	cmd = minishell->input_matrix[0];
	arg = minishell->input_matrix[1];

    if (minishell->args_num > 2)
        printf("minishell: %s: too many arguments\n", cmd);
    else if (minishell->args_num == 1)
        chdir(getenv("HOME"));
    else if (access(arg, F_OK))
        printf("minishell: %s: No such file or directory\n", arg);
    else
    {
        if (stat(arg, &buffer) || !S_ISDIR(buffer.st_mode))
            printf("minishell: cd: %s: Not a directory\n", arg);
        else if (access(arg, X_OK)) // chekiar
            printf("minishell: cd: %s: Permission denied\n", arg);
        else if (chdir(arg))
            printf("minishell: cd: %s: Failed to change directory\n", arg);
    }
}

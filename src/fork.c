/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:56:46 by antonimo          #+#    #+#             */
/*   Updated: 2025/02/05 14:33:58 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	exec_cmd(t_minishell *minishell, char **envp)
{
	if (minishell->built_in_type)
		exec_built_in(minishell, envp);
	else
		fork_exec(minishell, envp);
}*/

void	fork_exec(t_minishell *minishell, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if(execve(minishell->cmd_path, minishell->input_matrix, envp) != 0)
		{
			free_minishell(minishell);
			exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(pid, NULL, 0);
}

void	exec_built_in(t_minishell *minishell, char **envp)
{
	if (minishell->built_in_type == FT_PWD)
		ft_pwd(minishell);
	else if (minishell->built_in_type == FT_CD)
		ft_cd(minishell);
	/*else if (minishell->built_in_type == FT_ECHO)
		ft_echo(minishell);*/
	else if (minishell->built_in_type == FT_EXPORT)
		ft_export(minishell, envp);
	/*else if (minishell->built_in_type == FT_UNSET)
		ft_unset(minishell);
	else if (minishell->built_in_type == FT_ENV)
		ft_env(minishell);
	else if (minishell->built_in_type == FT_EXIT)
		ft_exit(minishell);*/
}

void	ft_export(t_minishell *minishell, char **envp)
{
	int		i;

	if (minishell->args_num > 1)
	{
		printf("minishell: %s: too many arguments\n", minishell->input_matrix[0]);
		return ;
	}
	i = 0;
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}

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
        else if (access(arg, X_OK))
            printf("minishell: cd: %s: Permission denied\n", arg);
        else if (chdir(arg))
            printf("minishell: cd: %s: Failed to change directory\n", arg);
    }
}

/*void	ft_cd(t_minishell *minishell)
{
    struct stat	buffer;

	if (minishell->input_matrix[2])
	{
		printf("minishell: %s: too many arguments\n", minishell->input_matrix[0]);
		return;
	}
    if(!minishell->input_matrix[1])
    {
        chdir(getenv("HOME"));
        return ;
    }
    if (access(minishell->input_matrix[1], F_OK) != 0)
    {
        printf("minishell: cd: %s: No such file or directory\n", minishell->input_matrix[1]);
        return ;
    }
    if (stat(minishell->input_matrix[1], &buffer) != 0 || !S_ISDIR(buffer.st_mode))
    {
        printf("minishell: cd: %s: Not a directory\n", minishell->input_matrix[1]);
        return ;
    }
    if (access(minishell->input_matrix[1], X_OK) != 0)
    {
        printf("minishell: cd: %s: Permission denied\n", minishell->input_matrix[1]);
        return ;
    }
    chdir(minishell->input_matrix[1]);
}*/

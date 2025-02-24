/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:56:46 by antonimo          #+#    #+#             */
/*   Updated: 2025/02/13 12:16:04 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_exec(t_minishell *minishell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if(execve(minishell->cmd_path, minishell->input_matrix, minishell->envp) != 0)
		{
			free_minishell(minishell);
			exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(pid, NULL, 0);
}

void	exec_built_in(t_minishell *minishell)
{
	if (minishell->built_in_type == FT_PWD)
	{
		ft_pwd(minishell);
		printf("\n");
	}
	else if (minishell->built_in_type == FT_CD)
		ft_cd(minishell);
	else if (minishell->built_in_type == FT_ECHO)
		ft_echo(minishell);
	/*else if (minishell->built_in_type == FT_EXPORT)
		ft_export(minishell);*/
	/*else if (minishell->built_in_type == FT_UNSET)
		ft_unset(minishell);*/
	else if (minishell->built_in_type == FT_ENV)
		ft_env(minishell);
	else if (minishell->built_in_type == FT_EXIT)
		ft_exit(minishell);
}

void	ft_export(t_minishell *minishell)
{
	int		i;

	if (minishell->args_num > 1)
	{
		printf("minishell: %s: too many arguments\n", minishell->input_matrix[0]);
		return ;
	}
	i = 0;
	while (minishell->envp[i])
	{
		printf("declare -x %s\n", minishell->envp[i]);
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
        else if (access(arg, X_OK)) // chekiar
            printf("minishell: cd: %s: Permission denied\n", arg);
        else if (chdir(arg))
            printf("minishell: cd: %s: Failed to change directory\n", arg);
    }
}

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

bool	ft_isnumber(t_minishell *minishell)
{
	int	i;

	i = 0;
	if (minishell->args_num == 2)
	{
		while (minishell->input_matrix[1][i])
		{
			if (!ft_isdigit(minishell->input_matrix[1][i]))
				return (false);
			i++;
		}	
	}
	return (true);
}
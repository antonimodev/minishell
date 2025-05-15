/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:40:18 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/24 12:55:37 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	    ft_cd(t_minishell *minishell);
static void	cd_path(t_minishell *minishell, char *arg);
static void cd_error_check(t_minishell *minishell, char *path);
static void	cd_old_pwd(t_minishell *minishell);
static void	cd_home(t_minishell *minishell);
static void	update_pwd(t_minishell *minishell, char *old_pwd);
static void set_env(t_minishell *minishell, char *env_var, char *value);
static bool find_in_matrix(char **matrix, char *var_name, int *index);

static bool find_in_matrix(char **matrix, char *var_name, int *index)
{
    *index = 0;
    while (matrix && matrix[*index])
    {
        if (!ft_strncmp(matrix[*index], var_name, ft_strlen(var_name)) && 
            (matrix[*index][ft_strlen(var_name)] == '=' || 
             matrix[*index][ft_strlen(var_name)] == '\0'))
            return (true);
        (*index)++;
    }
    return (false);
}

static void set_env(t_minishell *minishell, char *env_var, char *value)
{
    char	*new_var;
    int		i;
	
    i = 0;
	if (find_in_matrix(minishell->envp, env_var, &i))
	{
		env_var = ft_strjoin(env_var, "=");
		new_var = ft_strjoin(env_var, value);
		matrix_replace(minishell->envp, i, new_var);
		free(env_var);
		free(new_var);
	}
}

static void	update_pwd(t_minishell *minishell, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return ;
	set_env(minishell, "OLDPWD", old_pwd);
	set_env(minishell, "PWD", new_pwd);
	free(new_pwd);
}

static void	cd_home(t_minishell *minishell)
{
	char	*home;
	char	*old_pwd;

	home = ft_getenv(minishell->envp, "HOME=");
	if (!home || home[0] == '\0')
	{
		printf("minishell: cd: HOME not set\n");
		minishell->exit_status = 1;
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return ;
	if (chdir(home) == 0)
		update_pwd(minishell, old_pwd);
	else
		printf("minishell: cd: Failed to change directory %s\n", home);
	free(old_pwd);
}

static void	cd_old_pwd(t_minishell *minishell)
{
	char	*old_pwd;
	char	*pwd;

	old_pwd = ft_getenv(minishell->envp, "OLDPWD=");
	if (!old_pwd)
	{
		printf("minishell: cd: OLDPWD not set\n");
		minishell->exit_status = 1;
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	if (chdir(old_pwd) == 0)
		update_pwd(minishell, pwd);
	else
		printf("minishell: cd: Failed to change directory %s\n", old_pwd);
	free(pwd);
}

static void cd_error_check(t_minishell *minishell, char *path)
{
    struct stat info;

    if (access(path, F_OK))
    {
        printf("minishell: cd: %s: No such file or directory\n", path);
        minishell->exit_status = 1;
    }
    else if (stat(path, &info) != 0 || !S_ISDIR(info.st_mode))
    {
        printf("minishell: cd: %s: Not a directory\n", path);
        minishell->exit_status = 1;
    }
    else if (access(path, X_OK))
    {
        printf("minishell: cd: %s: Permission denied\n", path);
        minishell->exit_status = 1;
    }
    else
    {
        printf("minishell: cd: %s: Failed to change directory\n", path);
        minishell->exit_status = 1;
    }
}

static void	cd_path(t_minishell *minishell, char *arg)
{
	char	*old_pwd;

	if (arg[0] == '~')
	{
		cd_home(minishell);
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return ;
	if (chdir(arg) == 0)
		update_pwd(minishell, old_pwd);
	else
		cd_error_check(minishell, arg);
	free(old_pwd);
}

void	ft_cd(t_minishell *minishell)
{
	char	*arg;

	if (minishell->args_num > 2)
	{
		printf("minishell: cd: too many arguments\n");
		minishell->exit_status = 150;
		return ;
	}
	if (minishell->args_num == 1)
	{
		cd_home(minishell);
		return ;
	}
	arg = minishell->input_matrix[1];
	if (arg[0] == '-' && arg[1] == '\0')
		cd_old_pwd(minishell);
	else
		cd_path(minishell, arg);
}

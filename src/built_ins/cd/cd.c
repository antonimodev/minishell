/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:40:18 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/27 11:14:06 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_home(t_minishell *minishell)
{
	char	*home;
	char	*old_pwd;

	home = ft_getenv(minishell->envp, "HOME=");
	if (!home || home[0] == '\0')
		home = minishell->env_home;
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return ;
	if (chdir(home) == 0)
		update_pwd(minishell, old_pwd);
	else
	{
		ft_putstr_fd("minishell: cd: Failed to change directory ", 2);
		ft_putstr_fd(home, 2);
		ft_putstr_fd("\n", 2);
	}
	free(old_pwd);
}

static void	cd_old_pwd(t_minishell *minishell)
{
	char	*old_pwd;
	char	*pwd;

	old_pwd = ft_getenv(minishell->envp, "OLDPWD=");
	if (!old_pwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		minishell->exit_status = 1;
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	if (chdir(old_pwd) == 0)
	{
		printf("%s\n", old_pwd);
		update_pwd(minishell, pwd);
	}
	else
	{
		ft_putstr_fd("minishell: cd: Failed to change directory ", 2);
		ft_putstr_fd(old_pwd, 2);
		ft_putstr_fd("\n", 2);
	}
	free(pwd);
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
		cd_error(minishell, arg);
	free(old_pwd);
}

void	ft_cd(t_minishell *minishell)
{
	char	*arg;

	if (minishell->args_num > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		minishell->exit_status = 1;
		return ;
	}
	if (minishell->args_num == 1)
	{
		cd_home(minishell);
		return ;
	}
	arg = minishell->input_matrix[1];
	if (str_equal(arg, "-"))
		cd_old_pwd(minishell);
	else
		cd_path(minishell, arg);
}

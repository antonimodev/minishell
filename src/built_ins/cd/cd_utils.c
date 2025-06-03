/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:47:35 by jortiz-m          #+#    #+#             */
/*   Updated: 2025/06/03 15:27:43 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(t_minishell *minishell, char *env_var, char *value)
{
	char	*env_with_equal;
	char	*new_var;
	int		i;

	i = 0;
	env_with_equal = ft_strjoin(env_var, "=");
	new_var = ft_strjoin(env_with_equal, value);
	free(env_with_equal);
	if (find_in_matrix(minishell->envp, env_var, &i))
	{
		matrix_replace(minishell->envp, i, new_var);
		i = 0;
		if (minishell->declare_matrix
			&& find_in_matrix(minishell->declare_matrix, env_var, &i))
			matrix_replace(minishell->declare_matrix, i, new_var);
	}
	else
	{
		minishell->envp = matrix_append(minishell->envp, new_var);
		if (minishell->declare_matrix)
			minishell->declare_matrix = matrix_append
				(minishell->declare_matrix, new_var);
	}
	free(new_var);
}

void	update_pwd(t_minishell *minishell, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return ;
	set_env(minishell, "OLDPWD", old_pwd);
	set_env(minishell, "PWD", new_pwd);
	free(new_pwd);
}

bool	cd_access_error(t_minishell *minishell, char *path)
{
	if (access(path, F_OK))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(" No such file or directory\n", 2);
		minishell->exit_status = 1;
		return (true);
	}
	else if (access(path, X_OK))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		minishell->exit_status = 1;
		return (true);
	}
	return (false);
}

void	cd_error(t_minishell *minishell, char *path)
{
	struct stat	info;

	if (cd_access_error(minishell, path))
		return ;
	if (stat(path, &info) != 0 || !S_ISDIR(info.st_mode))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("a directory\n", 2);
		minishell->exit_status = 1;
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(" Failed to change directory\n", 2);
		minishell->exit_status = 1;
	}
}

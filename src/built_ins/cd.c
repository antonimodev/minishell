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

static void	cd_home(t_minishell *minishell);
static void	cd_error(t_minishell *minishell);
static char	*expand_tilde(t_minishell *minishell, char *arg);
static bool	valid_arg(t_minishell *minishell);

static char	*expand_tilde(t_minishell *minishell, char *arg)
{
	char	*home;
	char	*new_path;

	home = ft_getenv(minishell->envp, "HOME=");
	if (!home)
		return (NULL);
	new_path = ft_strjoin(home, arg + 1);
	free(arg);
	return (new_path);
}

static bool	valid_arg(t_minishell *minishell)
{
	char	*arg;

	arg = NULL;
	if (minishell->args_num == 2)
	{
		arg = ft_strdup(minishell->input_matrix[1]);
		if (access(arg, F_OK))
		{
			if (arg[0] == '~')
				arg = expand_tilde(minishell, arg);
		}
		if (!access(arg, F_OK))
			chdir(arg);
		else
		{
			printf("minishell: cd: %s: No such file or directory\n",
				minishell->input_matrix[1]);
			minishell->exit_status = 1;
		}
		free(arg);
		return (true);
	}
	return (false);
}

/**
 * @brief Changes the current working directory.
 *
 * This function handles the `cd` command in the minishell. It changes the
 * current working directory based on the arguments provided. If no arguments
 * are given, it changes to the home directory. It also handles various error
 * cases such as too many arguments, non-existent directories, non-directory
 * paths, and permission issues.
 *

	* @param minishell A pointer to the minishell structure containing the 
	input matrix and argument count.
 */
void	ft_cd(t_minishell *minishell)
{
	const char	*cmd;

	cmd = minishell->input_matrix[0];
	if (valid_arg(minishell))
		return ;
	if (minishell->args_num > 2)
	{
		printf("minishell: %s: too many arguments\n", cmd);
		minishell->exit_status = 150;
		return ;
	}
	if (minishell->args_num == 1)
		cd_home(minishell);
	else
		cd_error(minishell);
}

static void	cd_home(t_minishell *minishell)
{
	const char	*home;

	home = ft_getenv(minishell->envp, "HOME=");
	if (!home || home[0] == '\0')
	{
		printf("minishell: cd: No such file or directory\n");
		minishell->exit_status = 1;
		return ;
	}
	if (chdir(home))
	{
		printf("minishell: cd: %s: Failed to change directory\n", home);
		minishell->exit_status = 1;
	}
}

static void	cd_error(t_minishell *minishell)
{
	struct stat	buffer;
	const char	*path;
	char		*error_msg;

	error_msg = NULL;
	path = minishell->input_matrix[1];
	if (access(path, F_OK))
		error_msg = "No such file or directory";
	else if (stat(path, &buffer) || !S_ISDIR(buffer.st_mode))
		error_msg = "Not a directory";
	else if (access(path, X_OK))
		error_msg = "Permission denied";
	else if (chdir(path))
		error_msg = "Failed to change directory";
	if (error_msg)
	{
		printf("minishell: cd: %s: %s\n", path, error_msg);
		minishell->exit_status = 1;
	}
}

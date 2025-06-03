/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:29:06 by antonimo          #+#    #+#             */
/*   Updated: 2025/06/03 15:33:45 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	save_last_envp(t_minishell *minishell,
		char ***temp_envp, char ***temp_declare, char **system_envp)
{
	if (minishell->envp)
	{
		*temp_envp = matrix_cpy(minishell->envp, 0);
		free_matrix(minishell->envp);
	}
	else
		*temp_envp = matrix_cpy(system_envp, 0);
	if (minishell->declare_matrix)
	{
		*temp_declare = matrix_cpy(minishell->declare_matrix, 0);
		free_matrix(minishell->declare_matrix);
	}
	else
		*temp_declare = matrix_cpy(system_envp, 0);
}

static void	save_env_home(t_minishell *minishell, char **temp_home,
			char **system_envp)
{
	if (minishell->env_home)
		*temp_home = minishell->env_home;
	else
		*temp_home = ft_getenv(system_envp, "HOME=");
}

static void	set_last_envp(t_minishell *minishell, char ***temp_envp,
			char ***temp_declare)
{
	minishell->envp = matrix_cpy(*temp_envp, 0);
	minishell->declare_matrix = matrix_cpy(*temp_declare, 0);
	free_matrix(*temp_envp);
	free_matrix(*temp_declare);
}

void	update_minishell(t_minishell *minishell, char **system_envp)
{
	char	**temp_envp;
	char	**temp_declare;
	char	*temp_home;
	int		temp_exit_status;

	temp_exit_status = 0;
	save_last_envp(minishell, &temp_envp, &temp_declare, system_envp);
	save_env_home(minishell, &temp_home, system_envp);
	if (minishell->exit_status)
		temp_exit_status = minishell->exit_status;
	ft_memset(minishell, 0, sizeof(t_minishell));
	set_last_envp(minishell, &temp_envp, &temp_declare);
	minishell->env_home = temp_home;
	minishell->exit_status = temp_exit_status;
}

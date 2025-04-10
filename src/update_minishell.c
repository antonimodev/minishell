/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:49:01 by frmarian          #+#    #+#             */
/*   Updated: 2025/04/10 11:02:04 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_last_envp(t_minishell *minishell, bool *flag, \
	char ***temp_envp)
{
	if (minishell->envp)
	{
		*flag = true;
		*temp_envp = matrix_cpy(minishell->envp, 0);
		free_matrix(minishell->envp);
	}
}

static void	store_exit_status(t_minishell *minishell, int *temp_exit_status)
{
	if (minishell->exit_status)
		*temp_exit_status = minishell->exit_status;
}

static void	set_last_envp(t_minishell *minishell, char ***temp_envp, \
char **envp, bool flag)
{
	if (flag)
	{
		minishell->envp = matrix_cpy(*temp_envp, 0);
		free_matrix(*temp_envp);
	}
	else
		minishell->envp = matrix_cpy(envp, 0);
}

static void	update_exit_status(t_minishell *minishell, int temp_exit_status)
{
	if (temp_exit_status)
		minishell->exit_status = temp_exit_status;
}

void	update_minishell(t_minishell *minishell, char **system_envp)
{
	char	**temp_envp;
	int		temp_exit_status;
	bool	flag;

	temp_exit_status = 0;
	flag = false;
	check_last_envp(minishell, &flag, &temp_envp);
	if (minishell->exit_status)
		store_exit_status(minishell, &temp_exit_status);
	ft_memset(minishell, 0, sizeof(t_minishell));
	set_last_envp(minishell, &temp_envp, system_envp, flag);
	update_exit_status(minishell, temp_exit_status);
}

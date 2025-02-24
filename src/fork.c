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
	else if (minishell->built_in_type == FT_EXPORT)
		ft_export(minishell);
	/*else if (minishell->built_in_type == FT_UNSET)
		ft_unset(minishell);*/
	else if (minishell->built_in_type == FT_ENV)
		ft_env(minishell);
	else if (minishell->built_in_type == FT_EXIT)
		ft_exit(minishell);
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
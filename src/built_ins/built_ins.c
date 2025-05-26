/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:09:00 by jortiz-m          #+#    #+#             */
/*   Updated: 2025/05/22 10:32:15 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_built_in(t_minishell *minishell)
{
	if (!minishell->input_matrix ||!*minishell->input_matrix)
		return (false);
	if (ft_strcmp(minishell->input_matrix[0], "exit") == 0)
		minishell->built_in_type = FT_EXIT;
	else if (ft_strcmp(minishell->input_matrix[0], "echo") == 0)
		minishell->built_in_type = FT_ECHO;
	else if (ft_strcmp(minishell->input_matrix[0], "cd") == 0)
		minishell->built_in_type = FT_CD;
	else if (ft_strcmp(minishell->input_matrix[0], "pwd") == 0)
		minishell->built_in_type = FT_PWD;
	else if (ft_strcmp(minishell->input_matrix[0], "export") == 0)
		minishell->built_in_type = FT_EXPORT;
	else if (ft_strcmp(minishell->input_matrix[0], "unset") == 0)
		minishell->built_in_type = FT_UNSET;
	else if (ft_strcmp(minishell->input_matrix[0], "env") == 0)
		minishell->built_in_type = FT_ENV;
	else
	{
		minishell->built_in_type = FT_NULL;
		return (false);
	}
	return (true);
}

void	exec_built_in(t_minishell *minishell)
{
	//minishell->exit_status = 0; Esto reestablecia a 0 el exit status, checkear
	if (minishell->built_in_type == FT_PWD)
	{
		ft_pwd();
		printf("\n");
	}
	else if (minishell->built_in_type == FT_CD)
		ft_cd(minishell);
	else if (minishell->built_in_type == FT_ECHO)
		ft_echo(minishell);
	else if (minishell->built_in_type == FT_EXPORT)
		ft_export(minishell);
	else if (minishell->built_in_type == FT_UNSET)
		ft_unset(minishell);
	else if (minishell->built_in_type == FT_ENV)
		ft_env(minishell);
	else if (minishell->built_in_type == FT_EXIT)
		ft_exit(minishell);
	if (minishell->pid == CHILD)
	{
		free_minishell(minishell);
		exit(EXIT_SUCCESS);
	}
}

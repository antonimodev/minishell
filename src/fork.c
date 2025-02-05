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

// Hacer funcion que haga fork y execve del comando con flags y argumentos
void	fork_exec(t_minishell *minishell, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (minishell->built_in_type)
			exec_built_in(minishell);
		else if(execve(minishell->cmd_path, minishell->input_matrix, envp) != 0)
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
		ft_pwd(minishell);
/* 	else if (minishell->built_in_type == FT_CD)
		ft_cd(minishell);
	else if (minishell->built_in_type == FT_ECHO)
		ft_echo(minishell);
	else if (minishell->built_in_type == FT_EXPORT)
		ft_export(minishell); */
}

void	ft_pwd(t_minishell *minishell)
{
    char	*current_dir;

	getcwd(current_dir, 0);
	printf("%s\n", current_dir);
	free(current_dir);
}

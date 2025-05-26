/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:56:46 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/26 14:22:59 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_minishell *minishell)
{
	if (minishell->redir.invalid_input || !minishell->input_matrix)
		return ;
	redirect(minishell);
	if (!minishell->input_matrix || minishell->redir.invalid_input)
		return ;
	if (is_built_in(minishell))
	{
		exec_built_in(minishell);
		return ;
	}
	if (cmd_not_found(minishell))
		return ;
	fork_exec(minishell);
}

void	exec(t_minishell *minishell)
{
	if (execve(minishell->cmd_path, minishell->input_matrix,
			minishell->envp) != 0)
	{
		minishell->exit_status = 127;
		free_minishell(minishell);
		exit(EXIT_FAILURE);
	}
}

static void	get_exit_status(t_minishell *minishell, pid_t pid)
{
	waitpid(pid, &minishell->exit_status, 0);
	if (WIFEXITED(minishell->exit_status))
		minishell->exit_status = WEXITSTATUS(minishell->exit_status);
	else if (WIFSIGNALED(minishell->exit_status))
		minishell->exit_status = 128 + WTERMSIG(minishell->exit_status);
}

void	fork_exec(t_minishell *minishell)
{
	pid_t	pid;

	if (minishell->pid == CHILD)
		exec(minishell);
	else
	{
		pid = fork();
		if (pid == 0)
			exec(minishell);
		else
			get_exit_status(minishell, pid);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:56:46 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/11 14:26:03 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_minishell *minishell)
{
	if (minishell->user_input == NULL)
		return ;
	redirect(minishell);

	// Condicion provisional para evitar el "cmd not found"
	if (minishell->pid == PARENT && (minishell->redirection == REDIR_OUT
		|| minishell->redirection == REDIR_APPEND))
		return ;
	// 

	if (is_built_in(minishell))
	{
		exec_built_in(minishell);
		return ;
	}
	if (!minishell->cmd_path)
	{
		printf("minishell: %s: command not found\n",
			minishell->input_matrix[0]);
		minishell->exit_status = 127;
		return ;
	}
	fork_exec(minishell);
}
/* void	execute(t_minishell *minishell)
{
	if (minishell->user_input == NULL)
		return ;
	if (minishell->pid == CHILD)
		redirect(minishell);
	if (is_built_in(minishell))
	{
		exec_built_in(minishell);
		return ;
	}
	if (!minishell->cmd_path)
	{
		printf("minishell: %s: command not found\n",
			minishell->input_matrix[0]);
		minishell->exit_status = 127;
		return ;
	}
	fork_exec(minishell);
} */

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
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		minishell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		minishell->exit_status = 128 + WTERMSIG(status);
}

void	fork_exec(t_minishell *minishell)
{
	pid_t	pid;

	if (minishell->pid == CHILD)
		exec(minishell);
	else // ultimo comando
	{
		pid = fork();
		if (pid == 0)
			exec(minishell);
		else
			get_exit_status(minishell, pid);
	}
}


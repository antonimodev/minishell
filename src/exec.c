/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:56:46 by antonimo          #+#    #+#             */
/*   Updated: 2025/06/04 13:23:50 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_minishell *minishell)
{
	if (minishell->exit_status == 42)
	{
		minishell->exit_status = 130;
		return ;
	}
	if (minishell->redir.invalid_input || !minishell->input_matrix)
		return ;
	redirect(minishell);
	if (minishell->exit_status == 42)
	{
		minishell->exit_status = 130;
		return ;
	}
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
	close(minishell->fd_tools.stdin);
	close(minishell->fd_tools.stdout);
	close_unused_pipes(minishell);
	if (execve(minishell->cmd_path, minishell->input_matrix,
			minishell->envp) != 0)
	{
		minishell->exit_status = 127;
		free_minishell(minishell);
		exit(EXIT_FAILURE);
	}
}

void	get_exit_status(t_minishell *minishell, pid_t pid)
{
	waitpid(pid, &minishell->exit_status, 0);
	if (WIFEXITED(minishell->exit_status))
	{
		minishell->exit_status = WEXITSTATUS(minishell->exit_status);
		if (minishell->exit_status == 42)
			close_all_read_pipes(minishell);
	}
	else if (WIFSIGNALED(minishell->exit_status))
	{
		if (minishell->exit_status == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			close_unused_pipes(minishell);
			minishell->redir.invalid_input = true;
		}
		minishell->exit_status = 128 + WTERMSIG(minishell->exit_status);
	}
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
		{
			set_parent_signals();
			get_exit_status(minishell, pid);
		}
	}
}

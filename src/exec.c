/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:56:46 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/29 14:01:11 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	redir_exceptions(t_minishell *minishell)
{
	if (minishell->pid == CHILD &&
		(minishell->prev_redir == REDIR_APPEND || 
		minishell->prev_redir == REDIR_OUT))
	{
		free_minishell(minishell);
		exit(EXIT_SUCCESS);
	}

	if (minishell->pid == PARENT &&
		(minishell->redirection == REDIR_OUT ||
		minishell->redirection == REDIR_APPEND))
		return (true);

 	if (minishell->invalid_file) // revisar si exit_status lo coge bien
	{
		minishell->exit_status = INVALID_FILE;
		return (true);
	}
	return (false);
}

void	execute(t_minishell *minishell)
{
	if (minishell->user_input == NULL)
		return ;
	redirect(minishell);

	if (redir_exceptions(minishell))
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
	else // ultimo comando
	{
		pid = fork();
		if (pid == 0)
			exec(minishell);
		else
			get_exit_status(minishell, pid);
	}
}

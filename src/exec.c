/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:56:46 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/24 14:13:11 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_minishell *minishell)
{
	//print_minishell(minishell);
	//existe fd o redireccion? entonces entro en la funcion:
		// forkear para modificar valores de minishell en el hijo
		// funcion que hace toda la movida parseando el minishell->input_matrix
		// redireccionar a la pipe el resultado
		// fork_exec con la nueva info
	if (minishell->user_input == NULL)
		return ;
	if (is_built_in(minishell))
	{
		exec_built_in(minishell);
		return ;
	}
	if (!minishell->cmd_path)
	{
		printf("minishell: %s: command not found\n", minishell->input_matrix[0]);
		minishell->exit_status = 127;
		return ;
	}
	fork_exec(minishell);
}

void exec(t_minishell *minishell)
{
	if (execve(minishell->cmd_path, minishell->input_matrix, minishell->envp) != 0)
	{
	    minishell->exit_status = 127;
	    free_minishell(minishell);
	    exit(EXIT_FAILURE);
	}
}

void fork_exec(t_minishell *minishell) // LS | GREP "SRC"
{
	int		status;
	pid_t	pid;

	status = 0; // inicializar de prueba
	pid = 1; // inicializar de prueba
	if (minishell->pid == CHILD) // Si el input tiene una redirección (|, <, <<, >>)
	{
		redirect(minishell);
		exec(minishell);
	}
	else // Si soy un comando normal de toda la vida
		pid = fork();
	if (pid == 0)
	{
		exec(minishell);
		//print_minishell(minishell);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			minishell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			minishell->exit_status = 128 + WTERMSIG(status);
	}
}

bool	is_built_in(t_minishell *minishell)
{
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
	minishell->exit_status = 0;
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

	if (minishell->pid == CHILD) // Redirecciones se salen
		exit(EXIT_SUCCESS);
}

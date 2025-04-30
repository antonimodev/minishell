/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:42:25 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/11 13:42:25 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void foo_util(t_minishell *minishell, char *matrix_pos, char *redir_type)
{
	if (ft_strncmp(matrix_pos, ">>", 2) == 0)
		minishell->redirection = REDIR_APPEND;
	if (ft_strncmp(matrix_pos, "<<", 2) == 0)
		minishell->redirection = REDIR_HEREDOC;

	if (ft_strcmp(redir_type, "<<") == 0)
		minishell->prev_redir = REDIR_HEREDOC;
	else
		minishell->prev_redir = REDIR_IN;
}

static void	foo(t_minishell *minishell, char **matrix, int *current_pos,
    char *redir_type)
{
    (*current_pos)++;
    while (matrix[*current_pos])
    {
        if (!is_redirection(matrix[*current_pos], 0))
        {
            (*current_pos)++;
            continue;
		}
        if (ft_strncmp(matrix[*current_pos], redir_type, ft_strlen(redir_type)) == 0)
            (*current_pos)++;
        else
        {
			foo_util(minishell, matrix[*current_pos], redir_type);
            return;
        }
    }
    minishell->return_flag = true;
    (*current_pos)--;
    return;
}

/* static void	foo(t_minishell *minishell, char **matrix, int *current_pos)
{
    (*current_pos)++;
    while (matrix[*current_pos])
    {
        if (!is_redirection(matrix[*current_pos], 0))
        {
		    (*current_pos)++;
			continue ;
		}
        if (matrix[*current_pos][0] == REDIR_IN)
			(*current_pos)++;
		else if(matrix[*current_pos][0] != REDIR_IN)
		{
			minishell->redirection = matrix[*current_pos][0];
			minishell->prev_redir = REDIR_IN;
			return ;
		}
    }
	minishell->return_flag = true;
	(*current_pos)--;
    return ;
} */

static void	set_parent_input(t_minishell *minishell)
{
	t_pipe	pipe;

	if (minishell->pipe_tools.redir_count <= 0)
		return ;
	pipe = minishell->pipe_tools.pipes[minishell->pipe_tools.redir_count - 1];
	if (!minishell->redirection == REDIR_IN)
		close(pipe.write_pipe);
	fd_redirection(STDIN_FILENO, pipe.read_pipe);
	//close(pipe.read_pipe); No cerrar el pipe de lectura aquí, ya que se necesita para leer el contenido
	//del pipe en el proceso padre.
}

static bool	is_child_process(t_minishell *minishell, pid_t child)
{
	if (child == 0)
	{
		minishell->pid = CHILD;
		return (true);
	}
	return (false);
}

static bool	process_child_cmd(t_minishell *minishell, char **matrix,
	int *operator_pos, int *current_pos)
{
	pid_t	child;

	if (minishell->redirection == REDIR_IN)
		foo(minishell, matrix, current_pos, "<");
	else if (minishell->redirection == REDIR_HEREDOC)
		foo(minishell, matrix, current_pos, "<<");
	if (minishell->return_flag)
		return (false);
	else
	{
		child = fork();
		if (is_child_process(minishell, child))
		{
			minishell->input_matrix = matrix_from_matrix(matrix, *operator_pos,
					*current_pos);
			return (true);
		}
		else
		{
			close(minishell->pipe_tools.pipes[minishell->pipe_tools.redir_count
				- 1].write_pipe);
			waitpid(child, &minishell->exit_status, 0);
			if (WIFEXITED(minishell->exit_status))
				minishell->exit_status = WEXITSTATUS(minishell->exit_status);
		}
		*operator_pos = *current_pos + 1;
	}
	return (false);
}

void	handle_redir(t_minishell *minishell)
{
	int		i;
	int		operator_pos;
	char	**matrix;

	i = 0;
	operator_pos = 0;
	matrix = split_input(minishell);
	while (matrix[i])
	{
		if (is_redirection(matrix[i], 0))
		{
			add_redir(minishell);
			set_redir_type(minishell, matrix[i]);
			if (process_child_cmd(minishell, matrix, &operator_pos, &i))
			{
				free_matrix(matrix);
				return ;
			}
		}
		i++;
	}
	set_parent_input(minishell);
	minishell->input_matrix = matrix_from_matrix(matrix, operator_pos,
			matrix_len(matrix));
	free_matrix(matrix);
}

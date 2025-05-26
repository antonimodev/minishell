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

    child = fork();
    if (is_child_process(minishell, child))
    {
        free_matrix(minishell->input_matrix);
        minishell->input_matrix = matrix_from_matrix(matrix, *operator_pos,
                                                     *current_pos);
        return (true);
    }
    else
    {
    	close(minishell->fd_tools.pipes[minishell->redir.redir_count - 1].write_pipe);
        waitpid(child, &minishell->exit_status, 0);
        if (WIFEXITED(minishell->exit_status))
            minishell->exit_status = WEXITSTATUS(minishell->exit_status);
    }
    *operator_pos = *current_pos + 1;
    return (false);
}

void	handle_redir(t_minishell *minishell)
{
	int		i;
	int		operator_pos;
	char	**matrix;

	i = 0;
	operator_pos = 0;
	matrix = matrix_cpy(minishell->input_matrix, 0);
	while (matrix[i])
	{
		if (str_equal(matrix[i], "|"))
		{
			minishell_add_redir(minishell);
			minishell->first_cmd++;
			if (process_child_cmd(minishell, matrix, &operator_pos, &i))
			{
				free_matrix(matrix);
				return ;
			}
		}
		i++;
	}
	free_matrix(minishell->input_matrix);
	minishell->input_matrix = matrix_from_matrix(matrix, operator_pos,
			matrix_len(matrix));
	free_matrix(matrix);
}

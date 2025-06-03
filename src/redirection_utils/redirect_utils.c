/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:42:51 by antonimo          #+#    #+#             */
/*   Updated: 2025/06/03 13:03:02 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_heredoc_presence(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->input_matrix[i])
	{
		if (str_equal(minishell->input_matrix[i], "<<"))
			return (true);
		i++;
	}
	return (false);
}

void	handle_parent_pipe(t_minishell *minishell, bool has_heredoc)
{
	if (minishell->pid == PARENT)
	{
		if (minishell->first_cmd == 1)
			minishell->first_cmd++;
		if (minishell->first_cmd > 1 && !has_heredoc)
		{
			set_fd_mode(STDIN_FILENO,
				minishell->fd_tools.pipes[minishell->redir.redir_count - 1]);
			close_read_pipes(minishell);
		}
	}
}

void	handle_child_pipe(t_minishell *minishell, bool has_heredoc)
{
	if (minishell->pid == CHILD)
	{
		if (minishell->first_cmd == 1 && !has_heredoc)
			redir_first_cmd(minishell);
		else if (minishell->first_cmd > 1 && !has_heredoc)
			ft_pipe(minishell);
	}
}

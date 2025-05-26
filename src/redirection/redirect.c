/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:42:51 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/26 14:20:20 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_last_redirs(t_minishell *minishell, int index)
{
	int	last_fd;

	last_fd = index + 1;
	if (str_equal(minishell->input_matrix[index], "<"))
		minishell->redir.last_input = last_fd;
	if (str_equal(minishell->input_matrix[index], "<<"))
	{
		minishell->redir.last_input = last_fd;
		if (!minishell->heredoc.delimits)
			minishell->heredoc.delimits = create_matrix(0);
		minishell->heredoc.delimits = matrix_append(minishell->heredoc.delimits,
				minishell->input_matrix[last_fd]);
	}
	if (str_equal(minishell->input_matrix[index], ">")
		|| str_equal(minishell->input_matrix[index], ">>"))
		minishell->redir.last_output = last_fd;
}

static void	process_redir(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->input_matrix[i])
	{
		if (str_equal(minishell->input_matrix[i], "<<"))
			redir_heredoc(minishell, i);
		i++;
	}
	i = 0;
	while (minishell->input_matrix[i])
	{
		if (str_equal(minishell->input_matrix[i], ">>"))
			redir_append(minishell, i);
		else if (str_equal(minishell->input_matrix[i], ">"))
			redir_out(minishell, i);
		else if (str_equal(minishell->input_matrix[i], "<"))
			redir_in(minishell, i);
		i++;
	}
}

void	redirect(t_minishell *minishell)
{
	int		i;
	bool	has_heredoc;

	has_heredoc = check_heredoc_presence(minishell);
	handle_parent_pipe(minishell, has_heredoc);
	handle_child_pipe(minishell, has_heredoc);
	i = 0;
	while (minishell->input_matrix[i])
	{
		if (is_redirection(minishell->input_matrix[i]))
		{
			minishell->redir.redir_exist = true;
			set_last_redirs(minishell, i);
		}
		i++;
	}
	process_redir(minishell);
	if (minishell->pid == CHILD && has_heredoc)
		set_fd_mode(STDOUT_FILENO,
			minishell->fd_tools.pipes[minishell->redir.redir_count - 1]);
	if (minishell->redir.redir_exist)
		clean_matrix_redirs(minishell);
}

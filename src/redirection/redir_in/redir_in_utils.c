/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:31:24 by jortiz-m          #+#    #+#             */
/*   Updated: 2025/06/02 15:23:27 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_delimiter(t_minishell *minishell, char *line)
{
	int	index;

	index = minishell->heredoc.delimit_index;
	if (ft_strcmp(line, minishell->heredoc.delimits[index]) == 0)
	{
		free(line);
		minishell->heredoc.delimit_index++;
		return (true);
	}
	return (false);
}

void	handle_heredoc_eof(t_minishell *minishell)
{
	int	index;

	index = minishell->heredoc.delimit_index;
	printf("minishell: warning: here-document delimited by end-of-file ");
	printf("wanted ('%s')\n", minishell->heredoc.delimits[index]);
	minishell->heredoc.delimit_index++;
}

void	handle_heredoc_sigint(t_minishell *minishell, t_pipe *temp_pipe)
{
	close(temp_pipe->read_pipe);
	close(temp_pipe->write_pipe);
	if (minishell->first_cmd)
	{
		close_read_pipes(minishell);
		close(minishell->fd_tools.pipes
		[minishell->redir.redir_count - 1].read_pipe);
	}
	if (minishell->pid == CHILD)
	{
		close(minishell->fd_tools.stdin);
		close(minishell->fd_tools.stdout);
		free_matrix(minishell->envp);
		free_matrix(minishell->declare_matrix);
		close(minishell->fd_tools.pipes
		[minishell->redir.redir_count - 1].read_pipe);
		close(minishell->fd_tools.pipes
		[minishell->redir.redir_count - 1].write_pipe);
		free_minishell(minishell);
		exit(42);
	}
	else if (minishell->pid == PARENT)
		minishell->exit_status = 42;
	return ;
}

bool	check_eof_or_delimiter(t_minishell *minishell, char *line)
{
	if (line == NULL)
	{
		handle_heredoc_eof(minishell);
		return (true);
	}
	else if (is_delimiter(minishell, line))
	{
		if (minishell->pid == PARENT && minishell->first_cmd)
		{
			close_read_pipes(minishell);
			close(minishell->fd_tools.pipes
			[minishell->redir.redir_count - 1].read_pipe);
		}
		return (true);
	}
	return (false);
}

int	heredoc_loop(t_minishell *minishell, int last_fd, t_pipe temp_pipe)
{
	char	*line;

	while (1)
	{
		setup_heredoc_signs();
		line = readline("> ");
		if (g_signal == 42)
		{
			if (line)
				free(line);
			handle_heredoc_sigint(minishell, &temp_pipe);
			g_signal = 0;
			return (-1);
		}
		if (check_eof_or_delimiter(minishell, line))
			break ;
		if (minishell->redir.last_input == last_fd
			&& !minishell->redir.invalid_input)
			ft_putendl_fd(line, temp_pipe.write_pipe);
		free(line);
	}
	return (0);
}

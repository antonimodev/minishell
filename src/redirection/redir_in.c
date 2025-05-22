/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:42:51 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/22 10:51:39 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_in(t_minishell *minishell, int index)
{
	int	last_fd;
	int	file;

	last_fd = index + 1;
	if (access(minishell->input_matrix[last_fd], F_OK | R_OK) < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(minishell->input_matrix[last_fd], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		minishell->redir.invalid_input = true;
		return ;
	}
	file = open(minishell->input_matrix[last_fd], O_RDONLY, 444);
	if (file < 0)
	{
		perror("error al abrir en redir_in");
		return ;
	}
	if (minishell->redir.last_input == last_fd)
		fd_redirection(STDIN_FILENO, file);
	close(file);
}

static bool	is_delimiter(t_minishell *minishell, char *line)
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

static void	handle_heredoc_eof(t_minishell *minishell)
{
	int	index;

	index = minishell->heredoc.delimit_index;
	printf("minishell: warning: here-document delimited by end-of-file\
		 (wanted '%s')\n", minishell->heredoc.delimits[index]);
	minishell->heredoc.delimit_index++;
}

void	redir_heredoc(t_minishell *minishell, int index)
{
	int		last_fd;
	char	*line;
	t_pipe	temp_pipe;

	last_fd = index + 1;
	if (minishell->redir.last_input == last_fd)
		temp_pipe = create_pipe();
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			handle_heredoc_eof(minishell);
			break ;
		}
		else if (is_delimiter(minishell, line))
			break ;
		if (minishell->redir.last_input == last_fd
			&& !minishell->redir.invalid_input)
			ft_putendl_fd(line, temp_pipe.write_pipe);
		free(line);
	}
	if (minishell->redir.last_input == last_fd
		&& !minishell->redir.invalid_input)
		set_fd_mode(STDIN_FILENO, temp_pipe);
}

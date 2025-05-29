/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:42:51 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/29 13:50:34 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_handle_sign(int sign)
{
	if (sign == SIGINT)
		g_signal = 42; // custom
}

static void	setup_heredoc_signs(void)
{
	struct sigaction	sa_heredoc;
	struct sigaction	sa_quit;

	sa_heredoc.sa_handler = &heredoc_handle_sign;
	sa_heredoc.sa_flags = 0;
	sigemptyset(&sa_heredoc.sa_mask);
	if (sigaction(SIGINT, &sa_heredoc, NULL) == -1)
		perror("sigaction");
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		perror("sigaction");
}

void	redir_in(t_minishell *minishell, int index)
{
	int	last_fd;
	int	file;

	last_fd = index + 1;
	if (access(minishell->input_matrix[last_fd], F_OK | R_OK) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(minishell->input_matrix[last_fd], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
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
	printf("minishell: warning: here-document delimited by end-of-file ");
	printf("wanted ('%s')\n", minishell->heredoc.delimits[index]);
	minishell->heredoc.delimit_index++;
}

/* void	redir_heredoc(t_minishell *minishell, int index)
{
	int		last_fd;
	char	*line;
	t_pipe	temp_pipe;

	if (minishell->pid == PARENT)
		setup_signals(); // con esto funcionaría como dice el subject
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
} */

void	redir_heredoc(t_minishell *minishell, int index)
{
	int		last_fd;
	char	*line;
	t_pipe	temp_pipe;
	pid_t	child;

	child = 1;
	last_fd = index + 1;
	if (minishell->redir.last_input == last_fd)
		temp_pipe = create_pipe();

	if (minishell->pid == PARENT)
		child = fork();
	if (child == 0 || minishell->pid == CHILD)
	{
		setup_heredoc_signs();
		while (1)
		{
			line = readline("> ");
			if (g_signal == 42)
			{
				minishell_reset_fd(minishell);
				free(line);
				free_minishell(minishell);
				free_matrix(minishell->envp);
				free_matrix(minishell->declare_matrix);
				close(temp_pipe.write_pipe);
				close(temp_pipe.read_pipe);
				exit(SIGINT);
			}
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
	}
	else
	{
		set_parent_signals();
		close(temp_pipe.write_pipe);
		close(temp_pipe.read_pipe);
		get_exit_status(minishell, child);
		return ;
	}
	if (minishell->redir.last_input == last_fd
		&& !minishell->redir.invalid_input)
		set_fd_mode(STDIN_FILENO, temp_pipe);
}


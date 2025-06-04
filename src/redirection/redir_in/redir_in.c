/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:42:51 by antonimo          #+#    #+#             */
/*   Updated: 2025/06/04 13:21:45 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_handle_sign(int sign)
{
	if (sign == SIGINT)
	{
		g_signal = 42;
		write(STDOUT_FILENO, "\n", 1);
		close(STDIN_FILENO);
	}
}

void	setup_heredoc_signs(void)
{
	struct sigaction	sa_heredoc;
	struct sigaction	sa_quit;

	sa_heredoc.sa_handler = &heredoc_handle_sign;
	sa_heredoc.sa_flags = 0;
	sigemptyset(&sa_heredoc.sa_mask);
	if (sigaction(SIGINT, &sa_heredoc, NULL) == -1)
		perror("sigaction");
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
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

void	redir_heredoc(t_minishell *minishell, int index)
{
	int		last_fd;
	t_pipe	temp_pipe;

	last_fd = index + 1;
	if (minishell->redir.last_input == last_fd)
		temp_pipe = create_pipe();
	else
	{
		temp_pipe.read_pipe = -1;
		temp_pipe.write_pipe = -1;
	}
	if (heredoc_loop(minishell, last_fd, temp_pipe) == -1)
		return ;
	if (minishell->redir.last_input == last_fd
		&& !minishell->redir.invalid_input)
	{
		set_fd_mode(STDIN_FILENO, temp_pipe);
		if (minishell->pid == PARENT && minishell->first_cmd)
			close_all_read_pipes(minishell);
	}
}

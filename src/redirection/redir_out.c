/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:42:51 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/22 10:52:01 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_out(t_minishell *minishell, int index)
{
	int	file;
	int	last_fd;

	last_fd = index + 1;
	file = open(minishell->input_matrix[last_fd], O_CREAT | O_TRUNC | O_WRONLY,
			0644);
	if (file < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(minishell->input_matrix[last_fd], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		minishell->redir.invalid_input = true;
		return ;
	}
	if (minishell->redir.last_output == last_fd)
		fd_redirection(STDOUT_FILENO, file);
	close(file);
}

void	redir_append(t_minishell *minishell, int index)
{
	int	file;
	int	last_fd;

	last_fd = index + 1;
	file = open(minishell->input_matrix[last_fd], O_CREAT | O_APPEND | O_WRONLY,
			0644);
	if (file < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(minishell->input_matrix[last_fd], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		minishell->redir.invalid_input = true;
		return ;
	}
	if (minishell->redir.last_output == last_fd)
		fd_redirection(STDOUT_FILENO, file);
	close(file);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:46:33 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/27 10:53:17 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_first_cmd(t_minishell *minishell)
{
	int	current_pipe;

	current_pipe = minishell->redir.redir_count - 1;
	set_fd_mode(STDOUT_FILENO, minishell->fd_tools.pipes[current_pipe]);
	return ;
}

void	minishell_pipe_append(t_minishell *minishell, t_pipe *pipe)
{
	t_pipe	*tmp;
	int		i;

	tmp = malloc((minishell->redir.redir_count) * sizeof(t_pipe));
	if (!tmp)
	{
		ft_putstr_fd("minishell_pipe_append: malloc\n", 2);
		return ;
	}
	i = 0;
	while (i < minishell->redir.redir_count - 1)
	{
		tmp[i] = minishell->fd_tools.pipes[i];
		i++;
	}
	tmp[i] = *pipe;
	if (minishell->fd_tools.pipes)
		free(minishell->fd_tools.pipes);
	minishell->fd_tools.pipes = tmp;
}

void	minishell_add_redir(t_minishell *minishell)
{
	t_pipe	pipe;

	pipe = create_pipe();
	minishell->redir.redir_count++;
	minishell_pipe_append(minishell, &pipe);
}

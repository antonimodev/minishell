/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:31:53 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/11 13:36:58 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_redir_existence(t_minishell *minishell)
{
	if (!ft_strchr_gnl(minishell->user_input, '|')
		&& !ft_strchr_gnl(minishell->user_input, '<')
		&& !ft_strchr_gnl(minishell->user_input, '>'))
		return (false);
	minishell->redir_existence = true;
	return (true);
}

bool	check_valid_redir(t_minishell *minishell)
{
	if (is_redirection(minishell->user_input, 0)
		|| is_redirection(minishell->user_input,
			ft_strlen(minishell->user_input) - 1))
		return (false);
	return (true);
}

void	set_redir_type(t_minishell *minishell, char *str)
{
	if (minishell->redirection)
		minishell->prev_redir = minishell->redirection;
	if (str[0] == '|' && !str[1])
		minishell->redirection = PIPE;
	else if (str[0] == '<' && !str[1])
		minishell->redirection = REDIR_IN;
	else if (str[0] == '>' && !str[1])
		minishell->redirection = REDIR_OUT;
	else if (str[0] == '>' && str[1] == '>' && !str[2])
		minishell->redirection = REDIR_APPEND;
	else if (str[0] == '<' && str[1] == '<' && !str[2])
		minishell->redirection = REDIR_HEREDOC;
}

void	add_redir(t_minishell *minishell)
{
	t_pipe	pipe;

	pipe = create_pipe();
	minishell->pipe_tools.redir_count++;
	pipe_append(minishell, &pipe);
}

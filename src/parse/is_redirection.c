/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:15:12 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/22 11:32:15 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_double_redir(char *str)
{
	if (!str)
		return (false);
	if (ft_strlen(str) == 2 && ((ft_strncmp(str, ">>", 2) == 0
				|| ft_strncmp(str, "<<", 2) == 0)))
		return (true);
	return (false);
}

static bool	is_single_redir(char *str)
{
	if (!str)
		return (false);
	if (ft_strlen(str) == 1
		&& (ft_strncmp(str, ">", 1) == 0
			|| ft_strncmp(str, "<", 1) == 0
			|| ft_strncmp(str, "|", 1) == 0))
		return (true);
	return (false);
}

bool	is_redirection(char *str)
{
	if (is_single_redir(str) || is_double_redir(str))
		return (true);
	return (false);
}

bool	is_quoted_redir_or_pipe(char *str)
{
	char	*content;
	int		len;
	bool	result;

	if (!str || ft_strlen(str) < 3)
		return (false);
	len = ft_strlen(str);
	result = false;
	if ((str[0] == '"' && str[len - 1] == '"')
		|| (str[0] == '\'' && str[len - 1] == '\''))
	{
		content = ft_substr(str, 1, len - 2);
		if (!content)
			return (false);
		if (is_redirection(content))
			result = true;
		free(content);
	}
	return (result);
}

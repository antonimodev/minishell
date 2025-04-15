/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:06:26 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/11 14:08:09 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_surrounded(char *str, int index)
{
    if (index == 0 || !str[index + 1])
        return (false);
    if (index > 0 && !ft_isspace(str[index - 1]))
        return (true);
    if (str[index + 1] && !ft_isspace(str[index + 1]))
        return (true);
    return (false);
}

static void	add_spaces(char **clean_input, char *user_input, int *pos)
{
	char current_char;
	char prev_char;
	char next_char;

	current_char = user_input[*pos];
	next_char = user_input[*pos + 1];
	prev_char = user_input[*pos - 1];
	if (prev_char != ' ')
		*clean_input = str_append_char(*clean_input, ' ');
	*clean_input = str_append_char(*clean_input, current_char);
	if ((current_char == '>' || current_char == '<')
		&& next_char
		&& next_char == current_char)
	{
		*clean_input = str_append_char(*clean_input, next_char);
		(*pos)++;
	}
	if (next_char != ' ')
		*clean_input = str_append_char(*clean_input, ' ');
}

bool	is_redirection(char *str, int pos)
{
	if (!str || str[pos] == '\0')
		return (false);
	if (str[pos] == '|')
		return (true);
	else if (str[pos] == '>')
		return (true);
	else if (str[pos] == '<')
		return (true);
	return (false);
}

char	*expand_pipe(t_minishell *minishell)
{
	int		i;
	char	*clean_input;
	t_quote	quote;

	i = 0;
	quote.type = '\0';
	quote.closed = true;
	clean_input = ft_strdup("");
	while (minishell->user_input[i])
	{
		quote_state(minishell->user_input[i], &quote);
		if (is_redirection(minishell->user_input, i)
			&& is_surrounded(minishell->user_input, i)
			&& quote.closed)
			add_spaces(&clean_input, minishell->user_input, &i);
		else
			clean_input = str_append_char(clean_input,
					minishell->user_input[i]);
		i++;
	}
	free(minishell->user_input);
	return (clean_input);
}

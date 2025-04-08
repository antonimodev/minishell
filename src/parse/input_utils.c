/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:44:47 by frmarian          #+#    #+#             */
/*   Updated: 2025/04/07 12:5:57 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static char	*str_alloc(char **user_input)
{
	char	*str;
	int		len;

	len = count_with_spaces(*user_input);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	return (str);
} 
// "ls   "         "                -la"
// "ls   " "                -la"

char	*clean_input(t_minishell *minishell)
{
	int		i;
	int		len;
	char	*str;
	t_quote	quote;

	i = 0;
	len = 0;
	quote.type = '\0';
	quote.closed = true;
	minishell->user_input = strtrim_and_free(minishell->user_input, " ");
	str = str_alloc(&minishell->user_input);
	while (minishell->user_input[i])
	{
		if (valid_chr(minishell->user_input[i]))
		{
			quote_state(minishell->user_input[i], &quote);
			if (minishell->user_input[i] == ' ' && quote.closed)
				skip_middle_spaces(minishell->user_input, &i);
			str[len] = minishell->user_input[i];
			len++;
		}
		i++;
	}
	str[len] = '\0';
	free(minishell->user_input);
	return (str);
}

int	count_with_spaces(char *user_input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (user_input[i])
	{
		if (valid_chr(user_input[i]))
			count++;
		i++;
	}
	return (count);
}

/* 

int	count_with_spaces(char *user_input)
{
	int		i;
	int		count;
	t_quote	quote;

	i = 0;
	count = 0;
	quote.type = '\0';
	quote.closed = true;
	while (user_input[i])
	{
		if (valid_chr(user_input[i]))
		{
			quote_state(user_input[i], &quote);
			if (user_input[i] == ' ' && quote.closed)
				skip_middle_spaces(user_input, &i);
			count++;
		}
		i++;
	}
	return (count);
}

*/

bool	is_empty(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->user_input[i])
	{
		if (ft_isspace(minishell->user_input[i]))
			i++;
		else
			return (false);
	}
	free(minishell->user_input);
	minishell->user_input = NULL;
	return (true);
}

void	shell_prompt(t_minishell *minishell)
{
	char	*user;
	char	*pwd;
	char	*arrow;
	char	*prompt;

	user = minishell->user;
	pwd = getcwd(NULL, 0);
	user = ft_strjoin("\001" BOLD_TURQUOISE "\002", user);
	user = strjoin_and_free(user, "\001" RESET "\002");
	arrow = ft_strdup("\001" BOLD_GREEN "\002 ➜ \001" RESET "\002");
	prompt = strjoin_and_free(user, arrow);
	prompt = strjoin_and_free(prompt, pwd);
	prompt = strjoin_and_free(prompt, "\001" BOLD_YELLOW \
		"\002 ✦ \001" RESET "\002");
	minishell->shell_prompt = prompt;
	free(arrow);
	free(pwd);
}

bool	valid_chr(char c) //no_skip() previamente
{
	return (c != '\n' && c != '\t' && \
		c != '\v' && c != '\f' && c != '\r');
}

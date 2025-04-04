/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:44:47 by frmarian          #+#    #+#             */
	/*   Updated: 2025/03/17 11:19:23 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char	*str_alloc(char **user_input)
{
	char	*str;
	int		len;

	*user_input = custom_strtrim(*user_input, ' ');
	len = count_with_spaces(*user_input);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	return (str);
}

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
	str = str_alloc(&minishell->user_input);
	while (minishell->user_input[i])
	{
		if (no_skip(minishell->user_input[i]))
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
		if (no_skip(user_input[i]))
			count++;
		i++;
	}
	return (count);
}

bool	is_empty(t_minishell *minishell)
{
	int	i;

	i = 0;
	if (!minishell->user_input)
	{
		free_minishell(minishell);
		exit(EXIT_SUCCESS);
	}
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
	minishell->shell_prompt.user = ft_strjoin("\001" BOLD_TURQUOISE "\002", minishell->user);
	minishell->shell_prompt.user = ft_strjoin_gnl(minishell->shell_prompt.user, "\001" RESET "\002");
	
	minishell->shell_prompt.pwd = getcwd(NULL, 0);
	
	minishell->shell_prompt.arrow = ft_strdup("\001" BOLD_GREEN "\002 ➜ \001" RESET "\002");
	
	minishell->shell_prompt.prompt = ft_strjoin_gnl(minishell->shell_prompt.user, minishell->shell_prompt.arrow);
	free(minishell->shell_prompt.arrow);
	
	minishell->shell_prompt.prompt = ft_strjoin_gnl(minishell->shell_prompt.prompt, minishell->shell_prompt.pwd);
	free(minishell->shell_prompt.pwd);
	
	minishell->shell_prompt.prompt = ft_strjoin_gnl(minishell->shell_prompt.prompt, "\001" BOLD_YELLOW "\002 ✦ \001" RESET "\002");
}

bool	no_skip(char c)
{	
	return (c != '\n' && c != '\t' && \
		c != '\v' && c != '\f' && c != '\r');
}
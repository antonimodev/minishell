/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:44:47 by frmarian          #+#    #+#             */
/*   Updated: 2025/03/04 12:50:03 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clean_input(t_minishell *minishell)
{
	char *str;
	int len;
	int	i;

	minishell->user_input = custom_strtrim(minishell->user_input, ' ');
	len = count_with_spaces(minishell->user_input);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	len = 0;
	while (minishell->user_input[i])
	{
		if (no_skip(minishell->user_input[i]))
		{
			if (minishell->user_input[i] == ' ')
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
	while (minishell->user_input[i])
	{
		if (ft_isspace(minishell->user_input[i]))
			i++;
		else
			return (false);
	}
	free(minishell->user_input); // readline reserva mem, libera
	minishell->user_input = NULL;
	return (true);
}

void	shell_prompt(t_minishell *minishell)
{
    minishell->shell_prompt.user = ft_strjoin(BOLD_TURQUOISE, minishell->user);
    minishell->shell_prompt.user = ft_strjoin_gnl(minishell->shell_prompt.user, RESET);

    minishell->shell_prompt.pwd = getcwd(NULL, 0);

    minishell->shell_prompt.arrow = ft_strdup(BOLD_GREEN " ➜ " RESET);

    minishell->shell_prompt.prompt = ft_strjoin_gnl(minishell->shell_prompt.user, minishell->shell_prompt.arrow);
	free(minishell->shell_prompt.arrow);

    minishell->shell_prompt.prompt = ft_strjoin_gnl(minishell->shell_prompt.prompt, minishell->shell_prompt.pwd);
    free(minishell->shell_prompt.pwd);
    
    minishell->shell_prompt.prompt = ft_strjoin_gnl(minishell->shell_prompt.prompt, BOLD_YELLOW " ✦ " RESET);
}

bool	no_skip(char c)
{	
	return (c != '\\' && c != '\n' && c != '\t' && \
		c != '\v' && c != '\f' && c != '\r' && \
		c != ';');
}
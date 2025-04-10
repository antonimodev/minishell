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

static char	*mount_prompt(char **user, char **pwd, char **arrow, char **prompt)
{
	*user = ft_strjoin("\001" BOLD_TURQUOISE "\002", *user);
	*user = strjoin_and_free(*user, "\001" RESET "\002");
	*arrow = ft_strdup("\001" BOLD_GREEN "\002 ➜ \001" RESET "\002");
	*prompt = strjoin_and_free(*user, *arrow);
	*prompt = strjoin_and_free(*prompt, *pwd);
	*prompt = strjoin_and_free(*prompt, "\001" BOLD_YELLOW \
		"\002 ✦ \001" RESET "\002");
	free(*arrow);
	free(*pwd);
	return(*prompt);
}
void	shell_prompt(t_minishell *minishell)
{
	char		*pwd;
	char		*user;
	char		*arrow;
	char		*prompt;
	static char *last_prompt;
	
	user = minishell->user;
	pwd = getcwd(NULL, 0); // esto me devuelve la ruta en la que estoy
	if (!pwd)
	{
		minishell->shell_prompt = ft_strdup(last_prompt);
		return ;
	}
	if (last_prompt)
		free(last_prompt);
	minishell->shell_prompt = mount_prompt(&user, &pwd, &arrow, &prompt);
	last_prompt = ft_strdup(minishell->shell_prompt); //backup
}

bool	valid_chr(char c) //no_skip() previamente
{
	return (c != '\n' && c != '\t' && \
		c != '\v' && c != '\f' && c != '\r');
}

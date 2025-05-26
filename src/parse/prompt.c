/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:44:47 by frmarian          #+#    #+#             */
/*   Updated: 2025/05/21 12:41:47 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*mount_prompt(char **user, char **pwd, char **arrow, char **prompt)
{
	*user = ft_strjoin("\001" BOLD_TURQUOISE "\002", *user);
	*user = strjoin_and_free(*user, "\001" RESET "\002");
	*arrow = ft_strdup("\001" BOLD_GREEN "\002 ➜ \001" RESET "\002");
	*prompt = strjoin_and_free(*user, *arrow);
	*prompt = strjoin_and_free(*prompt, *pwd);
	*prompt = strjoin_and_free(*prompt,
			"\001" BOLD_YELLOW "\002 ✦ \001" RESET "\002");
	free(*arrow);
	free(*pwd);
	return (*prompt);
}

// En Shell_prompt hay un still reachable ya que al usar
// last_prompt como static no se libera nunca, ni siquiera cuando hacemos
// exit, que debería de liberarse, prob. tengamos que hacerla como parámetro
// y no liberarla hasta que sea necesario en casos específicos.

void	shell_prompt(t_minishell *minishell)
{
	char		*pwd;
	char		*user;
	char		*arrow;
	char		*prompt;
	static char	*last_prompt;

	user = minishell->user;
	if (!user)
		user = "undefined";
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		minishell->shell_prompt = ft_strdup(last_prompt);
		return ;
	}
	if (last_prompt)
		free(last_prompt);
	minishell->shell_prompt = mount_prompt(&user, &pwd, &arrow, &prompt);
	last_prompt = ft_strdup(minishell->shell_prompt);
}

/* void	shell_prompt(t_minishell *minishell)
{
	char		*pwd;
	char		*user;
	char		*arrow;
	char		*prompt;
	static char	*last_prompt;

	user = minishell->user;
	if (!user)
		user = "undefined";
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		minishell->shell_prompt = ft_strdup(minishell->last_prompt);
		return ;
	}
	if (minishell->last_prompt)
		free(minishell->last_prompt);
	minishell->shell_prompt = mount_prompt(&user, &pwd, &arrow, &prompt);
	minishell->last_prompt = ft_strdup(minishell->shell_prompt);
} */
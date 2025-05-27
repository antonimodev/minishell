/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:44:47 by frmarian          #+#    #+#             */
/*   Updated: 2025/05/27 12:43:19 by jortiz-m         ###   ########.fr       */
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

void	shell_prompt(t_minishell *minishell)
{
	char		*pwd;
	char		*user;
	char		*arrow;
	char		*prompt;

	user = minishell->user;
	if (!user)
		user = "undefined";
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot",
			2);
		ft_putstr_fd(" access parent directories: No such file or directory\n",
			2);
		pwd = ft_strdup(minishell->env_home);
		if (chdir(minishell->env_home))
			ft_putstr_fd("error jeje\n", 2);
	}
	minishell->shell_prompt = mount_prompt(&user, &pwd, &arrow, &prompt);
}

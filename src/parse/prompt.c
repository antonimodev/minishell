/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:29:45 by antonimo          #+#    #+#             */
/*   Updated: 2025/06/03 15:29:47 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*mount_prompt(char **user, char **pwd, char **arrow, char **prompt)
{
	*user = ft_strjoin("\001" BOLD_TURQUOISE "\002", *user);
	*user = strjoin_and_free(*user, "\001" RESET "\002");
	*arrow = ft_strdup("\001" BOLD_GREEN "\002 > \001" RESET "\002");
	*prompt = strjoin_and_free(*user, *arrow);
	*prompt = strjoin_and_free(*prompt, *pwd);
	*prompt = strjoin_and_free(*prompt,
			"\001" BOLD_YELLOW "\002 $ \001" RESET "\002");
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
			ft_putstr_fd("Cannot access directory\n", 2);
	}
	minishell->shell_prompt = mount_prompt(&user, &pwd, &arrow, &prompt);
}

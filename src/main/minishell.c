/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:56:44 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/29 13:35:57 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int	main(int ac, char **av, char **envp)
{
	t_minishell	minishell;
	char		**my_envp;

	(void)(ac);
	(void)(av);
	ft_memset(&minishell, 0, sizeof(t_minishell));
	my_envp = envp;
	if (!envp || !*envp)
		default_env(&my_envp);
	update_minishell(&minishell, my_envp);
	increment_shlvl(&minishell);
	while (1)
	{
		setup_signals();
		init_minishell(&minishell, my_envp);
		get_input(&minishell);
		parse_input(&minishell);
		execute(&minishell);
		minishell_reset_fd(&minishell);
		free_minishell(&minishell);
	}
	return (0);
}

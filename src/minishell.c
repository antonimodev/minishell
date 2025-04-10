/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:56:44 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/10 13:08:48 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_minishell	minishell;

	UNUSED(ac);
	UNUSED(av);
	ft_memset(&minishell, 0, sizeof(t_minishell));
	setup_signals();
	while (1)
	{
		init_minishell(&minishell, envp);
		get_input(&minishell);
		parse_input(&minishell);
		execute(&minishell);
		//print_minishell(&minishell);
		reset_pipes(&minishell);
		free_minishell(&minishell);
	}
	return (0);
}


//static last_prompt = ft_strdup(minishell->shell_prompt);

//EN EXIT Y EN CTRL + D
//if (minishell->shell_prompt)
	// free(minishell->shell_promt)	ANOTU
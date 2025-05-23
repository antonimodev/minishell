/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:56:44 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/29 13:30:25 by frmarian         ###   ########.fr       */
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
		//print_minishell(&minishell);
		execute(&minishell);
		reset_fd(&minishell);
		free_minishell(&minishell);
	}
	return (0);
}

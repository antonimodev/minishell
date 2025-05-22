/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:56:44 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/22 10:32:56 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_minishell	minishell;

	(void)(ac);
	(void)(av);
	ft_memset(&minishell, 0, sizeof(t_minishell));
	setup_signals();
	while (1)
	{
		init_minishell(&minishell, envp);
		get_input(&minishell);
		parse_input(&minishell);
		execute(&minishell);
		minishell_reset_fd(&minishell);
		free_minishell(&minishell);
	}
	return (0);
}

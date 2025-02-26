/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:56:44 by antonimo          #+#    #+#             */
/*   Updated: 2025/02/05 14:27:40 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_envp(t_minishell *minishell, char **envp)
{
	bool	flag;
	char	**envp_matrix;

	flag = false;
	if (minishell->envp)
	{
		flag = true;
		envp_matrix = matrix_cpy(minishell->envp, 0);
		free_matrix(minishell->envp);
	}
	ft_memset(minishell, 0, sizeof(t_minishell));
	if (flag)
	{
		minishell->envp = matrix_cpy(envp_matrix, 0);
		free_matrix(envp_matrix);
	}
	else
		minishell->envp = matrix_cpy(envp, 0);
}

void	init_minishell(t_minishell *minishell, char **envp)
{
	set_envp(minishell, envp);
	minishell->user = ft_getenv(minishell->envp, "USER=");
}

int main(int ac, char **av, char **envp)
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
		free_minishell(&minishell);
    }
    return (0);
}

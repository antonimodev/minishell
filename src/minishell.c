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

int main(int ac, char **av, char **envp)
{
	t_minishell	minishell;

	UNUSED(ac); // Macro definida para eliminar warning de params sin utilizar.
	UNUSED(av);
    while (1)
    {
		get_input(&minishell);
		parse_input(&minishell, envp);
		//check_built_in
		execute(&minishell, envp);
		free_minishell(&minishell);
    }
    return (0);
}

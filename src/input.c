/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:15:12 by antonimo          #+#    #+#             */
/*   Updated: 2025/02/05 14:27:38 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_input(t_minishell *minishell, char **envp)
{
	ft_memset(minishell, 0, sizeof(t_minishell));
	minishell->user = ft_getenv(envp, "USER=");
	while (!valid_input(minishell->user_input))
	{
		printf("%s ➜", minishell->user);
		ft_pwd(minishell);
	    minishell->user_input = readline(" $ "); // Al poner pwd no hace falta poner nada
		add_history(minishell->user_input);
	}
}

void 	parse_input(t_minishell *minishell, char **envp)
{
	minishell->input_matrix = ft_split(minishell->user_input, ' ');
	minishell->args_num = matrixlen(minishell->input_matrix);
	minishell->cmd_path = get_path(minishell->input_matrix, envp);
}

bool	valid_input(char *input)
{
    if (!input || input[0] == '\0')
	{
		free(input);
		return (false);
	}
	else if ((ft_strcmp(input, "exit") == 0))
	{
		free(input);
        exit(EXIT_FAILURE);
	}
    return true;
}

void	free_minishell(t_minishell *minishell)
{
	//free(minishell->user);
	free(minishell->user_input);
	free(minishell->cmd_path);
	free_matrix(minishell->input_matrix);
}

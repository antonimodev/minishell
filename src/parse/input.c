/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:15:12 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/07 13:52:52 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_input(t_minishell *minishell)
{
	while (!valid_input(minishell->user_input))
	{
		shell_prompt(minishell);
		minishell->user_input = readline(minishell->shell_prompt.prompt);
		if (minishell->user_input == NULL)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		if (!is_empty(minishell))
			add_history(minishell->user_input);
	}
}

void 	parse_input(t_minishell *minishell)
{
	if (!check_quotes_balance(minishell->user_input))
	{
		free(minishell->user_input);
		minishell->user_input = NULL;
		return ;
	}
	minishell->user_input = clean_input(minishell);
	// VALID -> TIENE DOLAR Y SE ENCUENTRA EN EL ENVIRONMENT
		//HAGO LA FUNCION QUE ESTAMOS HACIENDO
	/* minishell->user_input = handle_variable_expansion(minishell);
	if (!minishell->user_input)
		return; */
	set_expand_var(minishell);
	minishell->input_matrix = split_input(minishell);
	minishell->args_num = matrix_len(minishell->input_matrix); // set args_num
	minishell->cmd_path = get_path(minishell->input_matrix, minishell->envp);
}

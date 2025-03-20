/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:15:12 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/20 13:12:16 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_input(t_minishell *minishell)
{
	while (!valid_input(minishell))
	{
		shell_prompt(minishell);
		minishell->user_input = readline(minishell->shell_prompt.prompt);
		if (!is_empty(minishell))
			add_history(minishell->user_input);
		free(minishell->shell_prompt.prompt);
		minishell->shell_prompt.prompt = NULL;
	}
}

void	parse_input(t_minishell *minishell)
{
	minishell->user_input = clean_input(minishell);
	set_expand_var(minishell);
	set_pipes_or_redirection(minishell);
	minishell->args_num = matrix_len(minishell->input_matrix);
	minishell->cmd_path = get_path(minishell->input_matrix, minishell->envp);
}

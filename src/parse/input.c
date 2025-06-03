/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:15:12 by antonimo          #+#    #+#             */
/*   Updated: 2025/06/03 13:46:02 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_last_input(t_minishell *minishell)
{
	if (minishell->user_input)
	{
		free(minishell->user_input);
		minishell->user_input = NULL;
	}
}

void	get_input(t_minishell *minishell)
{
	while (!valid_rl_input(minishell))
	{
		shell_prompt(minishell);
		free_last_input(minishell);
		minishell->user_input = readline(minishell->shell_prompt);
		if (g_signal == SIGINT)
		{
			minishell->exit_status = 130;
			g_signal = 0;
		}
		add_history(minishell->user_input);
		free(minishell->shell_prompt);
		minishell->shell_prompt = NULL;
	}
}

void	parse_input(t_minishell *minishell)
{
	set_expand_var(minishell);
	if (check_redir_existence(minishell))
		minishell->user_input = expand_pipe(minishell);
	if (minishell->redir.redir_exist && check_valid_redir(minishell))
		handle_redir(minishell);
	else
	{
		if (minishell->input_matrix)
			free_matrix(minishell->input_matrix);
		minishell->input_matrix = split_without_quotes(minishell);
	}
	if (minishell->exit_status == 42)
		return ;
	if (!minishell->input_matrix || !*minishell->input_matrix)
	{
		free_matrix(minishell->input_matrix);
		minishell->input_matrix = NULL;
		return ;
	}
	minishell->args_num = matrix_len(minishell->input_matrix);
	minishell->cmd_path = get_path(minishell->input_matrix, minishell->envp);
}

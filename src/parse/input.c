/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:15:12 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/30 14:34:28 by frmarian         ###   ########.fr       */
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
	if (minishell->redir_existence && check_valid_redir(minishell))
		handle_redir(minishell);
	else
		minishell->input_matrix = split_input(minishell);

	if (isatty(STDIN_FILENO))
		fprintf(stderr, "STDIN es un TTY\n");
	else
		fprintf(stderr, "STDIN NO es un TTY\n");

	minishell->args_num = matrix_len(minishell->input_matrix);
	minishell->cmd_path = get_path(minishell->input_matrix, minishell->envp);
}

// CMD NORMAL -> Funciona readline
// CMD + REDIRECCION (<, <<) -> CAGADON

// ls | wc -> Ejecuta LS, readline coge el primer elemento de LS y le pasa el resto a WC.

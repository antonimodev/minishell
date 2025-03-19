/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:15:12 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/19 14:18:42 by frmarian         ###   ########.fr       */
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
	if (ft_strchr_gnl(minishell->user_input, '|')
	|| ft_strchr_gnl(minishell->user_input, '<'))
		minishell->user_input = expand_pipe(minishell);
	// minishell->input_matrix = split_input(minishell); ESTA LINEA PARA COMPROBACIONES,
	// BORRAR ELSE PA COMPROBAR
	// else
		minishell->input_matrix = split_input(minishell);
	/*---------------*/
	printf("%s", minishell->user_input);
	minishell->args_num = matrix_len(minishell->input_matrix);
	minishell->cmd_path = get_path(minishell->input_matrix, minishell->envp);
}

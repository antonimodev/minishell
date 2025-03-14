/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:43:25 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/14 13:11:17 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	valid_input(t_minishell *minishell)
{
	if (minishell->user_input == NULL ||
		minishell->user_input[0] == '\0' ||
		!check_quotes_balance(minishell->user_input))
	{
		free(minishell->user_input);
		return (false);
	}
	return (true);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:43:25 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/11 12:58:25 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	valid_input(t_minishell *minishell)
{
	if (minishell->user_input == NULL || minishell->user_input[0] == '\0')
	{
		free(minishell->user_input);
		return (false);
	}
	return (true);
}

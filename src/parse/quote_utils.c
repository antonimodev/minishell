/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:23:48 by frmarian          #+#    #+#             */
/*   Updated: 2025/04/11 14:25:39 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_state(char current_char, t_quote *quote)
{
	if (quote->closed && (current_char == '"' || current_char == '\''))
	{
		quote->closed = false;
		quote->type = current_char;
	}
	else if (!quote->closed && current_char == quote->type)
	{
		quote->closed = true;
		quote->type = '\0';
	}
}

bool	check_quotes_balance(char *str)
{
	int		i;
	t_quote	quote;

	i = 0;
	quote.type = '\0';
	quote.closed = true;
	while (str[i])
	{
		quote_state(str[i], &quote);
		i++;
	}
	return (quote.closed);
}

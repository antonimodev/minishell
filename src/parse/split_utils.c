/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:47:25 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/03 13:51:22 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_quotes_balance(char *str)
{
	int     i;
	t_quote quote;
	
	i = 0;
	quote.type = '\0';  // Initialize quote type
	quote.closed = true;
	
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (!quote.type)
			{
				quote.type = str[i];
				quote.closed = !quote.closed;
			}
			else if (str[i] == quote.type)
			{
				quote.closed = !quote.closed;
				quote.type = '\0';
			}
		}
		i++;
	}
	return (quote.closed);
}

char    *custom_strtrim(char *str, char c)
{
	int     start;
	int     end;
	int     len;
	int     i;
	char    *new_str;

	if (!str)
		return (NULL);
	start = 0;
	end = ft_strlen(str) - 1; // -1 para no leer desde null
	while (str[start] == c && str[start])
		start++;
	while (end > start && str[end] == c)
		end--;
	len = end - start + 1; // por quitarle -1 anteriormente
	new_str = malloc((len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (start <= end)
		new_str[i++] = str[start++];
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

void	skip_middle_spaces(char *user_input, int *i)
{
	while (user_input[*i] && user_input[*i] == ' ')
		(*i)++;
	if (user_input[*i] != '\0')
			(*i)--;
}

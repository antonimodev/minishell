/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:47:25 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/04 11:14:27 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool    init_vars(char ***matrix, char **word, t_quote *quote)
{
    *matrix = malloc(sizeof(char *));
    if (!*matrix)
        return false;
    
    ft_bzero(*matrix, sizeof(char *));
    *word = ft_strdup("");
    if (!*word)
    {
        free(*matrix);
        return false;
    }
    quote->closed = true;
    quote->type = '\0';
    return true;
}

char	*str_append_char(char *word, char c) // probablemente haya que mandarlo como ** para liberar
{
    size_t	len;
	char 	*new_str;
	
	len = ft_strlen(word);
    new_str = malloc(len + 2);
	len = 0;
    if (!new_str)
	    return NULL;
    while (word[len])
	{
		new_str[len] = word[len];
		len++;
	}
    new_str[len] = c;
	new_str[len + 1] = '\0';
    
    free(word); // liberar
    return (new_str);
}

bool	check_quotes_balance(char *str)
{
	int     i;
	t_quote quote;
	
	i = 0;
	quote.type = '\0';
	quote.closed = true;
	
	while (str[i])
	{
		quote_status(&quote,str[i]);
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

/* HAY QUE MOVERLA
void	quote_status(t_quote *quote, unsigned int index, char c)
{
	if (c == '"' || c == '\'')
	{
		if (!quote->type)
		{
			quote->type = c;
			quote->closed = !quote->closed;
		}
		else if (c == quote->type)
		{
			quote->closed = !quote->closed;
			quote->type = '\0';
		}
	}
}*/

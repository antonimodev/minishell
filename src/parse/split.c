/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:02:33 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/03 14:23:15 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* char	**addmatrix(char **matrix, char **word)
{
	int     i;
	int     len;
	char    **new_matrix;

	len = matrix_len(matrix);
	new_matrix = malloc(sizeof(char **) * (len + 2)); // + 1 por el nulo y + 1 por la nueva palabra \en caso de ser la primera iteracion, len = 0 y la primera pos para la nueva palabra y segunda para nulo
	if (!new_matrix)
		return NULL;
	i = 0;
	while (i < len)
	{
		new_matrix[i] = ft_strdup(matrix[i]);
		i++;
	}
	new_matrix[i] = ft_strdup(*word);
	new_matrix[i + 1] = NULL;
	free(*word);
	free_matrix(matrix);
	*word = ft_strdup("");
	return (new_matrix);
} */

char **addmatrix(char **matrix, char **word)
{
	char **new_matrix;

	new_matrix = matrix_append(matrix, *word);
	free(*word);
	*word = ft_strdup("");
	return (new_matrix);
}

char **finalize_parsing(char **matrix, char **word)
{
    if (*word && (*word)[0] != '\0')  // Check that word exists AND is not empty
    {
        matrix = addmatrix(matrix, word);
    }
    free(*word);
    return matrix;
}

void quote_state(char current_char, t_quote *quote)
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

char **process_character(char current_char, char **matrix, char **word, t_quote *quote)
{
	if (quote->closed)
	{
		if (current_char == ' ')
		{
			if ((*word)[0] != '\0')
				return addmatrix(matrix, word);
			return matrix;
		}
		else if (current_char == '"' || current_char == '\'')
			quote_state(current_char, quote);
		else
			*word = str_append_char(*word, current_char);
	}
	else
	{
		if (current_char == quote->type)
			quote_state(current_char, quote);
		else
			*word = str_append_char(*word, current_char);
	}
	return (matrix);
}

char **split_input(t_minishell *minishell)
{
	char **matrix;
	char *word;
	t_quote quote;
	int i;

	if (!minishell->user_input)
		return (NULL);
	if (!init_vars(&matrix, &word, &quote))
		return (NULL);
	i = 0;
	while (minishell->user_input[i])
	{
		if (valid_chr(minishell->user_input[i]))
		{
			if (minishell->user_input[i] == ' ' && quote.closed)
				skip_middle_spaces(minishell->user_input, &i);
			matrix = process_character(minishell->user_input[i], matrix, &word, &quote);
			if (!matrix)
				return (NULL);
		}
		i++;
	}
	return (finalize_parsing(matrix, &word));
}

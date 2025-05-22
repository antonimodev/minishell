/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:02:33 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/22 10:59:13 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_with_quotes(t_minishell *minishell)
{
	int		i;
	t_quote	quote;
	char	*word;
	char	**matrix;

	i = -1;
	quote.type = '\0';
	quote.closed = true;
	word = ft_strdup("");
	matrix = create_matrix(0);
	while (minishell->user_input[++i])
	{
		quote_state(minishell->user_input[i], &quote);
		if (minishell->user_input[i] == ' ' && quote.closed)
		{
			skip_middle_spaces(minishell->user_input, &i);
			matrix = addmatrix(matrix, &word);
		}
		else
			word = str_append_char(word, minishell->user_input[i]);
	}
	if (ft_strlen(word) > 0)
		matrix = addmatrix(matrix, &word);
	free(word);
	return (matrix);
}

char	**split_without_quotes(t_minishell *minishell)
{
	char	**matrix;
	char	*word;
	t_quote	quote;
	int		i;

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
			matrix = process_character(minishell->user_input[i], matrix, &word,
					&quote);
			if (!matrix)
				return (NULL);
		}
		i++;
	}
	return (finalize_parsing(matrix, &word));
}

char	**process_character(char current_char, char **matrix, char **word,
		t_quote *quote)
{
	if (quote->closed)
	{
		if (current_char == ' ')
		{
			if ((*word)[0] != '\0')
				return (addmatrix(matrix, word));
			return (matrix);
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

char	**addmatrix(char **matrix, char **word)
{
	char	**new_matrix;

	new_matrix = matrix_append(matrix, *word);
	free(*word);
	*word = ft_strdup("");
	return (new_matrix);
}

char	**finalize_parsing(char **matrix, char **word)
{
	if (*word && (*word)[0] != '\0')
		matrix = addmatrix(matrix, word);
	free(*word);
	return (matrix);
}

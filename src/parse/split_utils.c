/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:47:25 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/22 10:58:00 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	init_vars(char ***matrix, char **word, t_quote *quote)
{
	*matrix = malloc(1 * sizeof(char *));
	if (!*matrix)
		return (false);
	ft_bzero(*matrix, sizeof(char *));
	*word = ft_strdup("");
	if (!*word)
	{
		free(*matrix);
		return (false);
	}
	quote->closed = true;
	quote->type = '\0';
	return (true);
}

char	*str_append_char(char *word, char c)
{
	size_t	len;
	char	*new_str;

	new_str = malloc(ft_strlen(word) + 2);
	len = 0;
	if (!new_str)
		return (NULL);
	while (word[len])
	{
		new_str[len] = word[len];
		len++;
	}
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(word);
	return (new_str);
}

char	*strtrim_and_free(char *str, char *c)
{
	char	*new_str;

	if (!str)
		return (NULL);
	new_str = ft_strtrim(str, c);
	free(str);
	return (new_str);
}

void	skip_middle_spaces(char *user_input, int *i)
{
	int	start_i;

	start_i = *i;
	while (user_input[*i] && user_input[*i] == ' ')
		(*i)++;
	if (user_input[*i] == '\0')
		*i = start_i;
	else if (*i > start_i)
		(*i)--;
}

void	process_final_matrix(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->quoted_matrix[i])
	{
		if (is_quoted_redir_or_pipe(minishell->quoted_matrix[i]))
			matrix_replace(minishell->input_matrix, i,
				minishell->quoted_matrix[i]);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_cmd_cleaner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:10:50 by frmarian          #+#    #+#             */
/*   Updated: 2025/05/27 13:10:09 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_chr_from_str(char *str, char chr)
{
	char	*new_str;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	new_str = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != chr)
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

static void	foo(t_minishell *minishell, int *index)
{
	if (is_redirection(minishell->input_matrix[*index]))
	{
		minishell->input_matrix = matrix_substract
			(minishell->input_matrix, *index);
		if (minishell->input_matrix[*index])
			minishell->input_matrix = matrix_substract
				(minishell->input_matrix, *index);
	}
	else
	{
		if (is_quoted_redir_or_pipe(minishell->input_matrix[*index]))
		{
			minishell->input_matrix[*index] = remove_chr_from_str
				(minishell->input_matrix[*index], '"');
			minishell->input_matrix[*index] = remove_chr_from_str
				(minishell->input_matrix[*index], '\'');
		}
		(*index)++;
	}
}

void	clean_matrix_redirs(t_minishell *minishell)
{
	int		i;

	i = 0;
	while (minishell->input_matrix[i])
		foo(minishell, &i);
	if (!minishell->cmd_path)
		minishell->cmd_path = get_path
			(minishell->input_matrix, minishell->envp);
}

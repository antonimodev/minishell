/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_cmd_cleaner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:10:50 by frmarian          #+#    #+#             */
/*   Updated: 2025/05/26 14:21:35 by frmarian         ###   ########.fr       */
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

/* char	**clean_matrix_redirs(t_minishell *minishell)
{
	char	**new_matrix;
	int		end;

	end = 0;
	while (minishell->input_matrix[end])
	{
		if (is_redirection(minishell->input_matrix[end]))
			break ;
		if (is_quoted_redir_or_pipe(minishell->input_matrix[end]))
		{
			minishell->input_matrix[end] = remove_chr_from_str(minishell->\
								input_matrix[end], '"');
			minishell->input_matrix[end] = remove_chr_from_str(minishell->\
								input_matrix[end], '\'');
		}
		end++;
	}
	new_matrix = matrix_from_matrix(minishell->input_matrix, 0, end);
	free_matrix(minishell->input_matrix);
	return (new_matrix);
} */

/* char **clean_matrix_redirs(t_minishell *minishell)
{
	char	**new_matrix;
	int		i;

	i = 0;
	new_matrix = create_matrix(0);
	while (minishell->input_matrix[i])
	{
		if (!is_redirection(minishell->input_matrix[i]))
		{
			if (is_quoted_redir_or_pipe(minishell->input_matrix[i]))
			{
				minishell->input_matrix[i] = remove_chr_from_str(minishell->\
									input_matrix[i], '"');
				minishell->input_matrix[i] = remove_chr_from_str(minishell->\
									input_matrix[i], '\'');
			}
			matrix_append(new_matrix, minishell->input_matrix[i]);
		}
		i++;
	}
	free_matrix(minishell->input_matrix);
	return (new_matrix);
} */

/* void	clean_matrix_redirs(t_minishell *minishell)
{
	//char	**new_matrix;
	int		i;

	i = 0;
	//new_matrix = create_matrix(0);
	printf("matrix antes de bucle:\n\n");
	print_matrix(minishell->input_matrix);
	while (minishell->input_matrix[i])
	{
		if (is_redirection(minishell->input_matrix[i]))
		{
			minishell->input_matrix = matrix_substract(minishell->input_matrix, i);
			if (minishell->input_matrix[i])
				minishell->input_matrix  = matrix_substract(minishell->input_matrix, i);
		}
		else
		
		printf("minishell->input_matrix[%d] es: %s\n", i, minishell->input_matrix[i]);
		i++;
	}
 	printf("matrix despues de bucle:\n\n");
	print_matrix(minishell->input_matrix);
}
*/
void	clean_matrix_redirs(t_minishell *minishell)
{
    int		i;

    i = 0;
    while (minishell->input_matrix[i])
    {
        if (is_redirection(minishell->input_matrix[i]))
        {
            minishell->input_matrix = matrix_substract(minishell->input_matrix, i);
            if (minishell->input_matrix[i])
                minishell->input_matrix = matrix_substract(minishell->input_matrix, i);
        }
        else
        {
            if (is_quoted_redir_or_pipe(minishell->input_matrix[i]))
            {
                minishell->input_matrix[i] = remove_chr_from_str(minishell->\
                                    input_matrix[i], '"');
                minishell->input_matrix[i] = remove_chr_from_str(minishell->\
                                    input_matrix[i], '\'');
            }
            i++;
        }
    }
	if (!minishell->cmd_path)
		minishell->cmd_path = get_path(minishell->input_matrix, minishell->envp);
}

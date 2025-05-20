/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:10:50 by frmarian          #+#    #+#             */
/*   Updated: 2025/05/20 13:11:35 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *remove_chr_from_str(char *str, char chr);

char	**clean_matrix_redirs(t_minishell *minishell)
{
    char	**new_matrix;
    int		end;

    end = 0;
    while (minishell->input_matrix[end])
	{
		if (new_is_redirection(minishell->input_matrix[end]))
			break ;
		if (is_quoted_redir_or_pipe(minishell->input_matrix[end]))
		{
			minishell->input_matrix[end] = remove_chr_from_str(minishell->input_matrix[end], '"');
			minishell->input_matrix[end] = remove_chr_from_str(minishell->input_matrix[end], '\'');
		}
		end++;
	}
    new_matrix = matrix_from_matrix(minishell->input_matrix, 0, end);
    free_matrix(minishell->input_matrix);
    return (new_matrix);
}

static char *remove_chr_from_str(char *str, char chr)
{
    char    *new_str;
    int     i;
    int     j;

    if (!str)
        return (NULL);
    // Asignar memoria para el peor caso (ningún carácter eliminado)
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

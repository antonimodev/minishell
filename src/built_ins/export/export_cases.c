/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:09:48 by jortiz-m          #+#    #+#             */
/*   Updated: 2025/05/22 10:21:35 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_no_equal(t_minishell *minishell, char *arg)
{
	int	index;

	if (find_in_matrix(minishell->declare_matrix, arg, &index))
		return ;
	minishell->declare_matrix = matrix_append(minishell->declare_matrix, arg);
}

char	**export_equal(char **matrix, char *arg, char *var_name)
{
	int		index;
	bool	found;

	found = find_in_matrix(matrix, var_name, &index);
	if (found)
		matrix_replace(matrix, index, arg);
	else
		matrix = matrix_append(matrix, arg);
	return (matrix);
}

static char	**process_found_var(char **matrix, int index, char *var_name,
	char *arg_value)
{
	char	*value_ptr;
	char	*temp_str;
	char	*temp_str2;
	char	*final_str;

	value_ptr = matrix[index] + ft_strlen(var_name);
	if (*value_ptr == '=')
		value_ptr++;
	temp_str = ft_strjoin_at(value_ptr, arg_value, ft_strlen(value_ptr));
	temp_str2 = ft_strjoin(var_name, "=");
	final_str = strjoin_and_free(temp_str2, temp_str);
	free(temp_str);
	matrix_replace(matrix, index, final_str);
	free(final_str);
	return (matrix);
}

static char	**process_new_var(char **matrix, char *arg)
{
	char	*arg_modified;

	arg_modified = clean_chr_from_str(arg, '+');
	matrix = matrix_append(matrix, arg_modified);
	free(arg_modified);
	return (matrix);
}

char	**export_plus_equal(char **matrix, char *arg, char *var_name)
{
	int		index;
	bool	found;
	char	*arg_value;

	arg_value = ft_substr(arg, get_chr_index(arg, '=') + 1,
			ft_strlen(arg) - get_chr_index(arg, '='));
	found = find_in_matrix(matrix, var_name, &index);
	if (found)
		matrix = process_found_var(matrix, index, var_name, arg_value);
	else
		matrix = process_new_var(matrix, arg);
	free(arg_value);
	return (matrix);
}

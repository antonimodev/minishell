/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:40:45 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/22 10:43:31 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	var_matches(char *var, char *var_name, unsigned int var_name_len)
{
	return (!ft_strncmp(var, var_name, var_name_len)
		&& (var[var_name_len] == '=' || var[var_name_len] == '\0'));
}

static void	remove_var_from_matrix(char ***matrix, char *var_name,
			unsigned int var_name_len)
{
	unsigned int	i;

	i = 0;
	while ((*matrix)[i])
	{
		if (var_matches((*matrix)[i], var_name, var_name_len))
		{
			*matrix = matrix_substract(*matrix, i);
			break ;
		}
		i++;
	}
}

static void	unset_var(t_minishell *minishell, char *var_name)
{
	unsigned int	var_len;

	var_len = ft_strlen(var_name);
	remove_var_from_matrix(&minishell->envp, var_name, var_len);
	remove_var_from_matrix(&minishell->declare_matrix, var_name, var_len);
}

void	ft_unset(t_minishell *minishell)
{
	unsigned int	arg_i;

	if (minishell->args_num <= 1)
		return ;
	arg_i = 1;
	while (arg_i < (unsigned int)minishell->args_num)
	{
		if (!valid_symbols(minishell->input_matrix[arg_i]))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(minishell->input_matrix[arg_i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			minishell->exit_status = 1;
		}
		unset_var(minishell, minishell->input_matrix[arg_i]);
		arg_i++;
	}
}

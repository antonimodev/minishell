/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:40:45 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/26 12:04:07 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_unset(t_minishell *minishell)
{
    unsigned int	i;
    unsigned int	arg_i;
    unsigned int	var_len;

    arg_i = 1;
    if (minishell->args_num <= 1)
        return ;
    while (arg_i < (unsigned int)minishell->args_num)
    {
        var_len = ft_strlen(minishell->input_matrix[arg_i]);
        i = 0;
        while (minishell->envp[i])
        {
            if (!ft_strncmp(minishell->envp[i], minishell->input_matrix[arg_i], var_len)
            && (minishell->envp[i][var_len] == '=' || minishell->envp[i][var_len] == '\0'))
            {
                minishell->envp = matrix_substract(minishell->envp, i);
                break ;
            }
            i++;
        }
        arg_i++;
    }
}

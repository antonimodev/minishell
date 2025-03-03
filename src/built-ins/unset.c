/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:40:45 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/03 13:40:49 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_unset(t_minishell *minishell)
{
    unsigned int i;
    int arg_index;
    int var_len;

    if (minishell->args_num <= 1)
        return ;
    arg_index = 1;
    while (arg_index < minishell->args_num)
    {
        var_len = ft_strlen(minishell->input_matrix[arg_index]);
        i = 0;
        while (minishell->envp[i])
        {
            if (ft_strncmp(minishell->envp[i], minishell->input_matrix[arg_index], var_len) == 0
                && (minishell->envp[i][var_len] == '=' || minishell->envp[i][var_len] == '\0'))
            {
                minishell->envp = matrix_substract(minishell->envp, i);
                break ;
            }
            i++;
        }
        arg_index++;
    }
}

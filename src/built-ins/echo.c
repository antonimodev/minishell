/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:40:29 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/03 13:40:31 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_echo(t_minishell *minishell)
{
    int     i;
    bool    flag;

    i = 1;
    flag = false;
    while (minishell->input_matrix[i] && ft_strcmp(minishell->input_matrix[i], "-n") == 0)
    {
        flag = true;
        i++;
    }
    while (minishell->input_matrix[i])
    {
        printf("%s", minishell->input_matrix[i]);
        if (minishell->input_matrix[i + 1])
            printf(" ");
        i++;
    }
    if (!flag)
        printf("\n");
}

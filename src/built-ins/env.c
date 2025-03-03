/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:40:32 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/03 13:40:33 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_env(t_minishell *minishell)
{
    if (minishell->args_num > 1)
    {
        printf("This command executes without arguments\n");
        return ;
    }
    print_matrix(minishell->envp);
}

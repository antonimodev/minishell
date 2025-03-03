/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:41:13 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/03 13:41:14 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_minishell *minishell)
{
    char	*current_dir;

	if (minishell->args_num > 1)
	{
		printf("minishell: %s: too many arguments\n", minishell->input_matrix[0]);
		return ;
	}
	current_dir = getcwd(NULL, 0);
	printf("%s", current_dir);
	free(current_dir);
}

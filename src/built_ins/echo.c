/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:40:29 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/22 10:37:54 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid(const char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-' || str[1] == '\0')
		return (false);
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	ft_echo(t_minishell *minishell)
{
	int		i;
	bool	flag;

	i = 1;
	flag = false;
	while (minishell->input_matrix[i] && is_valid(minishell->input_matrix[i]))
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
	minishell->exit_status = 0;
}

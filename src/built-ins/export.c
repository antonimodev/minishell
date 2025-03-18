/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:41:27 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/18 13:49:57 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Si hacemos export hola=jeje y luego hacemos export hola=perro debería de sustituirse
// planteamiento: funcion que checkee si en nuestro minishell->envp existe "hola=" si es así,
// liberar esa variable de entorno y establecer en la misma posición una nueva con el contenido actualizado

void ft_export(t_minishell *minishell)
{
	int i;

	if (minishell->args_num > 2)
	{
		write(1, "\n", 1);
		return;
	}
	if (minishell->args_num == 2)
	{
		// esta condicion es para evitar duplicar la misma variable
		if (ft_getenv(minishell->envp, minishell->input_matrix[1]))
			return ;
		else if (valid_symbols(minishell->input_matrix[1]))
			minishell->envp = matrix_append(minishell->envp, minishell->input_matrix[1]);
		else
		{
			printf("%s not a valid identifier\n", minishell->input_matrix[1]);
			minishell->exit_status = 1;
		}
		return;
	}
	i = 0;
	while (minishell->envp[i])
	{
		printf("declare -x %s\n", minishell->envp[i]);
		i++;
	}
}

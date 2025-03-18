/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:41:27 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/18 14:25:26 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Si hacemos export hola=jeje y luego hacemos export hola=perro debería de sustituirse
// planteamiento: funcion que checkee si en nuestro minishell->envp existe "hola=" si es así,
// liberar esa variable de entorno y establecer en la misma posición una nueva con el contenido actualizado

// prototipo matrix_replace ->
// recibe minishell->envp, indice despues de buscar la coincidencia, y lo que quieres meter en ese indice

void matrix_replace(char **matrix, int index, char *new_value)
{
	free(matrix[index]);
	matrix[index] = ft_strdup(new_value);
}

void	foo(t_minishell *minishell)
{
	char	**env_matrix;
	char	*var_name;
	char	*var_value;

	// ASIGNACION DE NAME Y VALUE SI EL NOMBRE ES VALIDO
	if (valid_symbols(minishell->input_matrix[1]))
	{
		if (check_strchr_gnl(minishell->input_matrix[1], '='))
		{
			env_matrix = ft_split(minishell->input_matrix[1], '=');
			var_name = env_matrix[0];
			if (env_matrix[1])
				var_value = env_matrix[1];
			else
				var_value = NULL;
			free_matrix(env_matrix);
		}
	}
	// CHECKEAR EXISTE ESE NAME?
	if (ft_getenv(minishell->envp, var_name))
	{
		// sustituir nuevo valor con var_value matrix_replace()
	} else
		matrix_append(minishell->envp, minishell->input_matrix[1]);

}

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
		/*
			1. Hacer getenv del input_matrix[1]
			2. export hola=jeje -> hola=jeje
			3. export hola -> Depende del orden en el que exportemos, se duplica o no.
				Si hacemos hola=jeje > hola, solo se queda el primero.
				Si hacemos hola > hola=jeje, se ven las dos, no debería de ocurrir.
			4. export hola=perro -> Detecta diferencias y crea las dos, debería sustituir su valor.
		*/
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

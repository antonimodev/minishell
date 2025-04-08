/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:41:27 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/08 11:33:53 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Si hacemos export hola=jeje y luego hacemos export hola=perro debería de sustituirse
// planteamiento: funcion que checkee si en nuestro minishell->envp existe "hola=" si es así,
// liberar esa variable de entorno y establecer en la misma posición una nueva con el contenido actualizado

// prototipo matrix_replace ->
// recibe minishell->envp, indice despues de buscar la coincidencia, y lo que quieres meter en ese indice

static char *get_envp_var_name(char *env_var);
static int	ft_getenv_index(char **envp, char *env_var);
static void replace_env_var(t_minishell *minishell, char *var_name);
static void process_export_var(t_minishell *minishell);

static char	*get_envp_var_name(char *env_var)
{
	char	*var_name;
	int		i;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	var_name = ft_substr(env_var, 0, i);
	//var_name = strjoin_and_free(var_name, "="); esto era para el nombre con "="
	return (var_name);
}
// probablemente cambiemos el nombre o hagamos algo con la funcionalidad, es literalmente
// getenv solo que devuelve el índice.
static int	ft_getenv_index(char **envp, char *env_var)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(env_var);
    while (envp[i])
    {
        if (!ft_strncmp(envp[i], env_var, len))
            return (i);
        i++;
    }
    return (-1);
}
static void	replace_env_var(t_minishell *minishell, char *var_name)
{
	int	index;

	index = ft_getenv_index(minishell->envp, var_name);
	if (index < 0)
		return ;
	matrix_replace(minishell->envp, index, minishell->input_matrix[1]);
}

static void process_export_var(t_minishell *minishell)
{
    char *var_name;
    
    if (!valid_symbols(minishell->input_matrix[1]))
    {
        printf("minishell: export: '%s': not a valid identifier\n", minishell->input_matrix[1]);
        minishell->exit_status = 1;
        return ;
    }
    if (check_strchr_gnl(minishell->input_matrix[1], '='))
    {
        var_name = get_envp_var_name(minishell->input_matrix[1]);
        if (ft_getenv(minishell->envp, var_name))
			replace_env_var(minishell, var_name);
        else
            minishell->envp = matrix_append(minishell->envp, minishell->input_matrix[1]);
    }
    else
    {
        var_name = ft_strjoin(minishell->input_matrix[1], "=");
        if (!ft_getenv(minishell->envp, var_name))
            minishell->envp = matrix_append(minishell->envp, minishell->input_matrix[1]);
    }
	free(var_name);
}

void ft_export(t_minishell *minishell)
{
    int i;

	i = 0;
    if (minishell->args_num == 1)
    {
        while (minishell->envp[i])
        {
            printf("declare -x %s\n", minishell->envp[i]);
            i++;
        }
        return ;
    }
    else if (minishell->args_num == 2)
    {
        process_export_var(minishell);
        return ;
    }
    else
        write(1, "\n", 1);
}

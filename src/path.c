/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:56:28 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/12 13:53:42 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**set_raw(char **envp)
{
	char	*raw_env;
	char    **splitted_paths;

    raw_env = ft_getenv(envp, "PATH=");
	splitted_paths = ft_split(raw_env, ':');
    return(splitted_paths);
}

char    *get_path(char **input_matrix, char **envp)
{
    unsigned int    i;
    char	*cmd_path;
    char    **splitted_paths;

    if (!input_matrix)
        return (NULL);
    splitted_paths = set_raw(envp); // tiene memoria de split
    if (!splitted_paths)
        return (NULL);
    i = 0;
    while (envp[i])
    {
        if (ft_strcmp(envp[i], input_matrix[0]) == 0)
        {
            return (ft_strdup(input_matrix[0]));
            free_matrix(splitted_paths);
        }
        i++;
    }
    // recorrer toda la matriz y comprobar si mi user_input es un comando de ruta absoluta
        // return (ft_strdup(input_matrix[0]));
    splitted_paths = concat_paths(splitted_paths, input_matrix[0]);
    cmd_path = get_cmd_path(splitted_paths); //cmd_path tiene memoria
    free_matrix(splitted_paths);
    return (cmd_path);
}


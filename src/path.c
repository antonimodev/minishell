/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:56:28 by antonimo          #+#    #+#             */
/*   Updated: 2025/02/07 14:12:06 by antonimo         ###   ########.fr       */
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
    char	*cmd_path;
    char    **splitted_paths;

    if (!input_matrix)
        return (NULL);
    splitted_paths = set_raw(envp); // tiene memoria de split
    if (!splitted_paths)
        return (NULL);
    splitted_paths = concat_paths(splitted_paths, input_matrix[0]);
    cmd_path = get_cmd_path(splitted_paths); //cmd_path tiene memoria
    free_matrix(splitted_paths);
    return (cmd_path);
}

char    *ft_getenv(char **envp, char *env_var)
{
    int i;
    int len;
    
    i = 0;
    len = ft_strlen(env_var);
    while (envp[i])
    {
        if (ft_strncmp(envp[i], env_var, len) == 0)
            return (envp[i] + len);
        i++;
    }
    return (NULL);
}

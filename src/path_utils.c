/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:56:33 by antonimo          #+#    #+#             */
/*   Updated: 2025/02/07 14:12:37 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// OPCIONAL
	//comprobar strchr de "/", comprobar con stat y si es true, return strdup(cmd)
	//utilizar stat() en caso de que sea ruta relativa
	//usar access(F_OK, X_OK) para existencia y permisos
	//si me pasan ruta con "/" comprobar directamente
#include "minishell.h"

void	execute(t_minishell *minishell, char **envp)
{
	if (minishell->user_input == NULL)
		return ;
    if (is_built_in(minishell))
    {
        exec_built_in(minishell, envp);
        return;
    }
    if (!minishell->cmd_path)
    {
        printf("minishell: %s: command not found\n", minishell->input_matrix[0]);
        return;
    }
    fork_exec(minishell, envp);
}
bool	is_built_in(t_minishell *minishell)
{
	if (ft_strcmp(minishell->input_matrix[0], "exit") == 0)
		minishell->built_in_type = FT_EXIT;
	else if (ft_strcmp(minishell->input_matrix[0], "echo") == 0)
		minishell->built_in_type = FT_ECHO;
	else if (ft_strcmp(minishell->input_matrix[0], "cd") == 0)
		minishell->built_in_type = FT_CD;
	else if (ft_strcmp(minishell->input_matrix[0], "pwd") == 0)
		minishell->built_in_type = FT_PWD;
	else if (ft_strcmp(minishell->input_matrix[0], "export") == 0)
		minishell->built_in_type = FT_EXPORT;
	else if (ft_strcmp(minishell->input_matrix[0], "unset") == 0)
		minishell->built_in_type = FT_UNSET;
	else if (ft_strcmp(minishell->input_matrix[0], "env") == 0)
		minishell->built_in_type = FT_ENV;
	else
	{
		minishell->built_in_type = FT_NULL;
		return (false);
	}
	return (true);
}

char	**concat_paths(char **splitted_path, char *cmd)
{
	int		i;

	i = 0;
	while (splitted_path[i])
	{
		splitted_path[i] = cmdcat(splitted_path[i], cmd);
		i++;
	}
	return (splitted_path);
}

char	*cmdcat(char *path, char *cmd)
{
	char	*filepath;
	int		path_len;
	int		cmd_len;

	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	filepath = malloc ((path_len + cmd_len + 2) * sizeof(char)); // para "/" y "\0"
	if (!filepath)
		return (NULL);
	filepath = ft_strcpy(filepath, path);
	filepath = ft_strcat(filepath, "/");
	filepath = ft_strcat(filepath, cmd);
	free(path);
	return (filepath);
}

char 	*get_cmd_path(char **splitted_paths)
{
	int	i;

	i = 0;
	while (splitted_paths[i])
	{
		if (is_valid(splitted_paths[i]))
			return (ft_strdup(splitted_paths[i]));
		i++;
	}
	return (NULL);
}

bool	is_valid(char *cmd_path)
{
    struct stat	buffer;

    if (access(cmd_path, F_OK | X_OK)
        || stat(cmd_path, &buffer)
        || !S_ISREG(buffer.st_mode)
        || !(buffer.st_mode & S_IXUSR))
        return (false);
    return (true);
}

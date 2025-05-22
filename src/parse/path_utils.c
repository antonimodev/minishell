/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:56:33 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/22 10:56:57 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	filepath = malloc ((path_len + cmd_len + 2) * sizeof(char));
	if (!filepath)
		return (NULL);
	filepath = ft_strcpy(filepath, path);
	filepath = ft_strcat(filepath, "/");
	filepath = ft_strcat(filepath, cmd);
	free(path);
	return (filepath);
}

char	*get_cmd_path(char **splitted_paths)
{
	int	i;

	i = 0;
	while (splitted_paths[i])
	{
		if (valid_cmd(splitted_paths[i]))
			return (ft_strdup(splitted_paths[i]));
		i++;
	}
	return (NULL);
}

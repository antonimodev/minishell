/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:56:28 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/11 14:08:12 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**set_raw(char **envp)
{
	char	*raw_env;
	char	**splitted_paths;

	raw_env = ft_getenv(envp, "PATH=");
	splitted_paths = ft_split(raw_env, ':');
	return (splitted_paths);
}

char	*get_path(char **input_matrix, char **envp)
{
	char	*cmd_path;
	char	**splitted_paths;

	if (!input_matrix)
		return (NULL);
	if (valid_cmd(input_matrix[0]))
	{
		cmd_path = ft_strdup(input_matrix[0]);
		return (cmd_path);
	}
	splitted_paths = set_raw(envp);
	if (!splitted_paths)
		return (NULL);
	splitted_paths = concat_paths(splitted_paths, input_matrix[0]);
	cmd_path = get_cmd_path(splitted_paths);
	free_matrix(splitted_paths);
	return (cmd_path);
}

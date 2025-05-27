/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:03:56 by frmarian          #+#    #+#             */
/*   Updated: 2025/05/27 10:53:17 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	valid_cmd(char *cmd_path)
{
	struct stat	buffer;

	if (access(cmd_path, F_OK | X_OK) || stat(cmd_path, &buffer)
		|| !S_ISREG(buffer.st_mode) || !(buffer.st_mode & S_IXUSR))
		return (false);
	return (true);
}

bool	cmd_not_found(t_minishell *minishell)
{
	if (!minishell->input_matrix || !*minishell->input_matrix)
		return (true);
	if (!minishell->cmd_path && !is_built_in(minishell))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(minishell->input_matrix[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		minishell->exit_status = CMD_NOT_FOUND;
		return (true);
	}
	return (false);
}

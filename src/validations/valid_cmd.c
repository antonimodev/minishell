/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:03:56 by frmarian          #+#    #+#             */
/*   Updated: 2025/05/21 14:05:09 by frmarian         ###   ########.fr       */
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
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(minishell->input_matrix[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		minishell->exit_status = CMD_NOT_FOUND;
		return (true);
	}
	return (false);
}

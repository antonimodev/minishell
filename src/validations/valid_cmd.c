/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:03:56 by frmarian          #+#    #+#             */
/*   Updated: 2025/04/11 14:04:00 by frmarian         ###   ########.fr       */
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

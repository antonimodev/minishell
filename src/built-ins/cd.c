/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:40:18 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/13 10:49:09 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Changes the current working directory.
 *
 * This function handles the `cd` command in the minishell. It changes the
 * current working directory based on the arguments provided. If no arguments
 * are given, it changes to the home directory. It also handles various error
 * cases such as too many arguments, non-existent directories, non-directory
 * paths, and permission issues.
 *
 * @param minishell A pointer to the minishell structure containing the input matrix and argument count.
 */
void	ft_cd(t_minishell *minishell)
{
	struct stat	buffer;
    const char	*cmd;
    const char	*arg;
	
	cmd = minishell->input_matrix[0];
	if (minishell->input_matrix[1])
		arg = minishell->input_matrix[1];
	else
		arg = NULL;

    if (minishell->args_num > 2)
        printf("minishell: %s: too many arguments\n", cmd);
    else if ((arg && arg[0] == '~') || minishell->args_num == 1)
        chdir(getenv("HOME"));
    else if (access(arg, F_OK))
        printf("minishell: %s: No such file or directory\n", arg);
    else
    {
        if (stat(arg, &buffer) || !S_ISDIR(buffer.st_mode))
            printf("minishell: cd: %s: Not a directory\n", arg);
        else if (access(arg, X_OK)) // chekiar
            printf("minishell: cd: %s: Permission denied\n", arg);
        else if (chdir(arg))
            printf("minishell: cd: %s: Failed to change directory\n", arg);
    }
}

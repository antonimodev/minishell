/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:50:46 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/13 11:42:04 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(t_minishell *minishell, char **envp)
{
	// cambiar nombre a set_envp -> checkpoint()?
	set_envp(minishell, envp);
	minishell->user = ft_getenv(minishell->envp, "USER=");
}

void	set_envp(t_minishell *minishell, char **envp)
{
	bool	flag;
	char	**envp_matrix;
	int		last_exit_status; // añadido

	flag = false;
	last_exit_status = 0;
	if (minishell->envp)
	{
		flag = true;
		envp_matrix = matrix_cpy(minishell->envp, 0);
		free_matrix(minishell->envp);
	}

	if (minishell->exit_status) // si existe, guardamos el estado de salida
		last_exit_status = minishell->exit_status;
	ft_memset(minishell, 0, sizeof(t_minishell));
	if (flag)
	{
		minishell->envp = matrix_cpy(envp_matrix, 0);
		free_matrix(envp_matrix);
	}
	else
		minishell->envp = matrix_cpy(envp, 0);

	if (last_exit_status)
		minishell->exit_status = last_exit_status;
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

void	free_minishell(t_minishell *minishell)
{
	if (minishell->user_input)
		free(minishell->user_input);
	if (minishell->cmd_path)
		free(minishell->cmd_path);
	if (minishell->input_matrix)
		free_matrix(minishell->input_matrix);
	if (minishell->shell_prompt.prompt)
		free(minishell->shell_prompt.prompt);
}

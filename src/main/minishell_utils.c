/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:50:46 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/27 12:54:38 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(t_minishell *minishell, char **envp)
{
	update_minishell(minishell, envp);
	minishell_store_fd(minishell);
	minishell->pid = PARENT;
	minishell->user = ft_getenv(minishell->envp, "USER=");
	minishell->user_input = ft_strdup("");
}

char	*ft_getenv(char **envp, char *env_var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(env_var);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], env_var, len))
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
	if (minishell->quoted_matrix)
		free_matrix(minishell->quoted_matrix);
	if (minishell->fd_tools.pipes)
		free(minishell->fd_tools.pipes);
	if (minishell->heredoc.delimits)
		free_matrix(minishell->heredoc.delimits);
}

void	increment_shlvl(t_minishell *minishell)
{
	char	*shlvl_str;
	char	*new_shlvl_str;
	int		shlvl_value;
	int		i;
	char	*var_with_equal;

	shlvl_str = ft_getenv(minishell->envp, "SHLVL=");
	if (!shlvl_str)
		shlvl_value = 1;
	else
		shlvl_value = ft_atoi(shlvl_str) + 1;
	new_shlvl_str = ft_itoa(shlvl_value);
	var_with_equal = ft_strjoin("SHLVL=", new_shlvl_str);
	i = 0;
	if (find_in_matrix(minishell->envp, "SHLVL", &i))
	{
		matrix_replace(minishell->envp, i, var_with_equal);
		matrix_replace(minishell->declare_matrix, i, var_with_equal);
	}
	else
		minishell->envp = matrix_append(minishell->envp, var_with_equal);
	free(new_shlvl_str);
	free(var_with_equal);
}

void	default_env(char ***system_envp)
{
	*system_envp = create_matrix(5);
	if (!*system_envp)
		return ;
	(*system_envp)[0] = ft_strdup("HOME=/");
	(*system_envp)[1] = ft_strdup("USER=minishell");
	(*system_envp)[2] = ft_strdup("SHLVL=1");
	(*system_envp)[3] = ft_strjoin("PWD=", getcwd(NULL, 0));
	(*system_envp)[4] = ft_strdup("OLDPWD=/");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:56:44 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/22 10:32:56 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void increment_shlvl(t_minishell *minishell)
{
	char	*shlvl_str;
	char	*new_shlvl_str;
	int		shlvl_value;
	int		i;
	char	*var_with_equal;

	shlvl_str = ft_getenv(minishell->envp, "SHLVL=");
	if (!shlvl_str)
		shlvl_value = 1; // O el que sea por defecto que no se cual es
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

static void default_env(char ***system_envp)
{
	*system_envp = create_matrix(5);
	if (!*system_envp)
		return;
		
	(*system_envp)[0] = ft_strdup("HOME=/");
	(*system_envp)[1] = ft_strdup("USER=minishell");
	(*system_envp)[2] = ft_strdup("SHLVL=1");
	(*system_envp)[3] = ft_strjoin("PWD=", getcwd(NULL, 0));
	(*system_envp)[4] = ft_strdup("OLDPWD=/");
}

int main(int ac, char **av, char **envp)
{
	t_minishell minishell;
	char **my_envp;

	(void)(ac);
	(void)(av);
	ft_memset(&minishell, 0, sizeof(t_minishell));
	my_envp = envp;
	if (!envp || !*envp)
		default_env(&my_envp);
	update_minishell(&minishell, my_envp);
	increment_shlvl(&minishell);
	setup_signals();
	while (1)
	{
		init_minishell(&minishell, my_envp);
		get_input(&minishell);
		parse_input(&minishell);
		execute(&minishell);
		minishell_reset_fd(&minishell);
		free_minishell(&minishell);
	}
	return (0);
}

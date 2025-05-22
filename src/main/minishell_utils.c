/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:50:46 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/22 10:44:00 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(t_minishell *minishell, char **envp)
{
	/*if (!envp || !*envp)
	{
		Seguramente función para inicializar un entorno personalizado de minishell
		Es importante que con el entorno personalizado funcione como hasta ahora.
	}*/
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
	if (minishell->shell_prompt)
		free(minishell->shell_prompt);
	if (minishell->fd_tools.pipes)
		free(minishell->fd_tools.pipes);
	if (minishell->heredoc.delimits)
		free_matrix(minishell->heredoc.delimits);
}

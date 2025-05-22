/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:08:29 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/22 11:00:57 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_name(t_minishell *minishell, char **var_name,
			unsigned int *i)
{
	*var_name = ft_strdup("");
	while (minishell->user_input[*i]
		&& valid_env_char(minishell->user_input[*i]))
		*var_name = str_append_char(*var_name, minishell->user_input[(*i)++]);
	*var_name = strjoin_and_free(*var_name, "=");
	return (*var_name);
}

static char	*set_env_var(t_minishell *minishell, unsigned int *i)
{
	char	*var_name;
	char	*var_value;

	(*i)++;
	if (!minishell->user_input[*i])
	{
		(*i)--;
		return (ft_strdup("$"));
	}
	if (minishell->user_input[*i] == '?')
		return (ft_itoa(minishell->exit_status));
	if (!valid_env_char(minishell->user_input[*i]))
		return (ft_strdup("$"));
	var_name = get_var_name(minishell, &var_name, i);
	var_value = ft_getenv(minishell->envp, var_name);
	free(var_name);
	(*i)--;
	if (var_value)
		return (ft_strdup(var_value));
	else
		return (ft_strdup(""));
}

static void	handle_variable_expansion(t_minishell *minishell, unsigned int *i,
									char **expanded_input, t_quote quote)
{
	char	*var_value;

	var_value = NULL;
	if (minishell->user_input[*i] == '$' && quote.type != '\'')
		var_value = set_env_var(minishell, i);
	if (var_value)
	{
		*expanded_input = strjoin_and_free(*expanded_input, var_value);
		free(var_value);
	}
	else
		*expanded_input = str_append_char(*expanded_input,
				minishell->user_input[*i]);
}

static char	*expand(t_minishell *minishell)
{
	unsigned int	i;
	t_quote			quote;
	char			*expanded_user_input;

	i = 0;
	quote.type = '\0';
	quote.closed = true;
	expanded_user_input = ft_strdup("");
	while (minishell->user_input[i])
	{
		quote_state(minishell->user_input[i], &quote);
		handle_variable_expansion(minishell, &i, &expanded_user_input, quote);
		i++;
	}
	return (expanded_user_input);
}

void	set_expand_var(t_minishell *minishell)
{
	char	*expanded_var;

	if (!minishell->user_input || !ft_strchr_gnl(minishell->user_input, '$'))
		return ;
	expanded_var = expand(minishell);
	if (expanded_var)
	{
		free(minishell->user_input);
		minishell->user_input = expanded_var;
	}
}

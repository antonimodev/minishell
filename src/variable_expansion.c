/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:08:29 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/13 11:41:26 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand(t_minishell *minishell);
static char	*set_env_var(t_minishell *minishell, unsigned int *i);
static bool	is_valid_var_char(char c);

static bool	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*set_env_var(t_minishell *minishell, unsigned int *i)
{
	char	*var_name;
	char	*var_value;

	var_name = ft_strdup("");
	(*i)++;
	if (!minishell->user_input[*i]
		|| !is_valid_var_char(minishell->user_input[*i]))
	{
		free(var_name);
		(*i)--;
		return (ft_strdup("$"));
	} else if (minishell->user_input[*i] == '?') // si la siguiente del $ es ?, devolvemos el estado en forma de str
	{
		free(var_name);
		(*i)--;
		return (ft_itoa(minishell->exit_status));
	}
	while (minishell->user_input[*i]
		&& is_valid_var_char(minishell->user_input[*i]))
		var_name = str_append_char(var_name, minishell->user_input[(*i)++]);
	var_value = ft_getenv(minishell->envp, var_name);
	if (var_value)
		var_value = ft_strdup(var_value + 1);
	else
		var_value = ft_strdup("");
	free(var_name);
	(*i)--;
	return (var_value);
}

static void	handle_variable_expansion(t_minishell *minishell, unsigned int *i, 
	char **expanded_user_input, t_quote quote)
{
	char	*var_value;

	var_value = NULL;
	if (minishell->user_input[*i] == '$' && quote.type != '\'')
		var_value = set_env_var(minishell, i);
	if (var_value)
	{
		*expanded_user_input = ft_strjoin_gnl(*expanded_user_input, var_value);
		free(var_value);
	}
	else
		*expanded_user_input = str_append_char(*expanded_user_input, 
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
	char *expanded_var;

	if (!minishell->user_input || !ft_strchr_gnl(minishell->user_input, '$'))
		return ;
	printf("Exit status: %d", minishell->exit_status);
	expanded_var = expand(minishell);
	if (expanded_var)
	{
		free(minishell->user_input);
		minishell->user_input = expanded_var;
	}
}
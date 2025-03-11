#include "minishell.h"

// Formato -> [ORDEN] + 2 palabras (como máximo)
/*
- GET
- SET
- EXIT
- VALID
- UPDATE
*/
static char	*expand(t_minishell *minishell);
static char *set_env_var(t_minishell *minishell, unsigned int *i);
static bool is_valid_var_char(char c);

static bool is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*set_env_var(t_minishell *minishell, unsigned int *i)
{
	char	*var_name;
	char	*var_value;
	char	*clean_value;
	
	(*i)++;
	var_name = ft_strdup("");
	while (minishell->user_input[*i] && is_valid_var_char(minishell->user_input[*i]))
	{
		var_name = str_append_char(var_name, minishell->user_input[*i]);
		(*i)++;
	}

	var_value = ft_getenv(minishell->envp, var_name);
	if (var_value)
		clean_value = ft_strdup(var_value + 1);
	free(var_name);
	return (clean_value);
}

static char	*expand(t_minishell *minishell)
{
	unsigned int	i;
	t_quote 		quote;
	char			*expanded_user_input;
	char			*var_value;

	i = 0;
	quote.type = '\0';
	quote.closed = true;
	expanded_user_input = ft_strdup("");
	while (minishell->user_input[i])
	{
		if (minishell->user_input[i] == '$' && quote.type != '\'')
		{
			var_value = set_env_var(minishell, &i);
			expanded_user_input = ft_strjoin_gnl(expanded_user_input, var_value);
		}
		else
			expanded_user_input = str_append_char(expanded_user_input, minishell->user_input[i]);
		i++;
	}
	free(var_value);
	return (expanded_user_input);
}

// minishell->user_input = set_expand_var();
void	set_expand_var(t_minishell *minishell)
{
	char	*expanded_var;

	if (!ft_strchr_gnl(minishell->user_input, '$'))
		return ;
	expanded_var = expand(minishell);
	free(minishell->user_input);
	minishell->user_input = ft_strdup(expanded_var);
	free(expanded_var);
}

#include "minishell.h"

bool is_pipe_or_redirection_at_pos(const char *str, int pos)
{
    if (!str || str[pos] == '\0')
        return (false);
    
    if (str[pos] == '|')
        return (true);
    else if (str[pos] == '>')
    {
        if (str[pos + 1] && str[pos + 1] == '>')  // Check for ">>"
            return (true);
        return (true);  // Single ">"
    }
    else if (str[pos] == '<')
    {
        if (str[pos + 1] && str[pos + 1] == '<')  // Check for "<<"
            return (true);
        return (true);  // Single "<"
    }
    
    return (false);
}

static bool is_surrounded(char *str, int index)
{
	if (index == 0 || !str[index + 1] || !str[index - 1])
		return (false);
	if (str[index - 1]
	&&	str[index + 1]
	&&	(!ft_isspace(str[index - 1])
	||	!ft_isspace(str[index + 1])))
		return (true);
	return (false);
}

static void add_spaces(char **clean_input, char *user_input, int *pos)
{
	if (user_input[*pos - 1] != ' ')
		*clean_input = str_append_char(*clean_input, ' ');
	*clean_input = str_append_char(*clean_input, user_input[*pos]);
	if ((user_input[*pos] == '>' || user_input[*pos] == '<')
	&&	user_input[*pos + 1]
	&&	user_input[*pos + 1] == user_input[*pos])
	{
		*clean_input = str_append_char(*clean_input, user_input[*pos + 1]);
		(*pos)++;
	}
	if (user_input[*pos + 1] != ' ')
		*clean_input = str_append_char(*clean_input, ' ');
}


char *expand_pipe(t_minishell *minishell)
{
	int i;
	char *clean_input;
	t_quote quote;
	
	i = 0;
	quote.type = '\0';
	quote.closed = true;
	clean_input = ft_strdup("");
	while (minishell->user_input[i])
	{
		quote_state(minishell->user_input[i], &quote);
		if (is_pipe_or_redirection_at_pos(minishell->user_input, i) && 
			is_surrounded(minishell->user_input, i) && 
			quote.closed)
			add_spaces(&clean_input, minishell->user_input, &i);
		else
			clean_input = str_append_char(clean_input, minishell->user_input[i]);
		i++;
	}
	free(minishell->user_input);
	return (clean_input);
}

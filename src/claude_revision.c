// claude revision:
#include "minishell.h"

static char *expand_variables(t_minishell *minishell);
static bool process_variable(t_minishell *minishell, char **result, unsigned int *pos);
static bool is_valid_var_char(char c);
static char *extract_var_name(char *input, unsigned int *pos);

static	char *expand_variables(t_minishell *minishell)
{
	char *result = ft_strdup("");
    t_quote quote = {.type = '\0', .closed = true};
    unsigned int i = 0;
    
    if (!result)
	    return NULL;
    
    while (minishell->user_input[i]) {
        // Update quote state
        quote_state(minishell->user_input[i], &quote);
        
        // Handle variable expansion outside single quotes
        if (minishell->user_input[i] == '$' && quote.type != '\'')
		{
            if (!process_variable(minishell, &result, &i))
			{
				free(result);
                return NULL;
            }
        }
		else
		{
            // Regular character
            result = str_append_char(result, minishell->user_input[i]);
            if (!result)
                return NULL;
		}
			i++;
		}
	return result;
}

// Process a variable and add its value to result
static bool process_variable(t_minishell *minishell, char **result, unsigned int *pos)
{
	
	char *var_name;
	char *new_result;
	char *var_value;
	
	var_name = ft_strdup(""); // Initialize
	extract_var_name(minishell->user_input, var_name, pos);
    if (!var_name)
		return false;
	var_value = ft_getenv(minishell->envp, var_name);
	if (var_value)
	{
		new_result = ft_strjoin_gnl(*result, var_value);
		if (!new_result)
		{
			free(var_name);
			return false;
		}
	result = new_result;
	}
	free(var_name);
	return true;
}

// Check if character is valid for variable names
static bool is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

// Extract variable name after $ sign
static void *extract_var_name(char *input, char *var_name, unsigned int *pos)
{
	(*pos)++; // Skip the $ character
	// Extract alphanumeric variable name
	while (input[*pos] && is_valid_var_char(input[*pos]))
	{
		var_name = str_append_char(var_name, input[*pos]);
		(*pos)++;
	}
	(*pos)--; // Adjust because main loop will increment
}

char	*handle_variable_expansion(t_minishell *minishell)
{
	// Skip if no $ characters
	if (!ft_strchr_gnl(minishell->user_input, '$'))
		return (NULL);
	
	char *expanded = expand_variables(minishell);
	if (!expanded)
		return (NULL);
	
	// Replace original input with expanded version
	free(minishell->user_input);
	return (expanded);
}

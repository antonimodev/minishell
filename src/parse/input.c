/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:15:12 by antonimo          #+#    #+#             */
/*   Updated: 2025/02/17 13:49:25 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool check_quotes_balance(char *str);


void get_input(t_minishell *minishell)
{   
	while (!valid_input(minishell->user_input))
	{
		shell_prompt(minishell);
	    minishell->user_input = readline(BOLD_YELLOW " ✦ " RESET); // Al poner pwd no hace falta poner nada
		if (!is_empty(minishell))
			add_history(minishell->user_input);
	}
}

bool	is_empty(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->user_input[i])
	{
		if (ft_isspace(minishell->user_input[i]))
			i++;
		else
			return (false);
	}
	free(minishell->user_input); // readline reserva mem, libera
	minishell->user_input = NULL;
	return (true);
}

void	shell_prompt(t_minishell *minishell)
{
	printf(BOLD_TURQUOISE "%s" RESET, minishell->user);
	printf(BOLD_GREEN " ➜ " RESET);
	ft_pwd(minishell);
}

void 	parse_input(t_minishell *minishell)
{
	minishell->user_input = clean_input(minishell);
	if (!check_quotes_balance(minishell->user_input))
    {
        free(minishell->user_input);
        minishell->user_input = NULL;
        return ;
    }
	minishell->input_matrix = think_v2(minishell);
	minishell->cmd_path = get_path(minishell->input_matrix, minishell->envp);
}

bool	valid_input(char *input)
{
    if (!input || input[0] == '\0')
	{
		free(input);
		return (false);
	}
	// Hemos movido el "exit" para hacerlo en un built-in
	return (true);
}

void	free_minishell(t_minishell *minishell)
{
	//free(minishell->user);
	if (minishell->user_input)
		free(minishell->user_input);
	if (minishell->cmd_path)
		free(minishell->cmd_path);
	if (minishell->input_matrix)
		free_matrix(minishell->input_matrix);
}

char	*clean_input(t_minishell *minishell)
{
    char *str;
    int len;
    int	i;

	minishell->user_input = custom_strtrim(minishell->user_input, ' ');
    len = count_with_spaces(minishell->user_input);
    str = malloc(sizeof(char) * (len + 1));
    if (!str)
        return (NULL);
    i = 0;
    len = 0;
    while (minishell->user_input[i])
    {
		if (no_skip(minishell->user_input[i]))
        {
			if (minishell->user_input[i] == ' ')
				skip_middle_spaces(minishell->user_input, &i);
            str[len] = minishell->user_input[i];
            len++;
        }
        i++;
    }
    str[len] = '\0';
    free(minishell->user_input);
    return (str);
}

int	count_with_spaces(char *user_input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (user_input[i])
	{
		if (no_skip(user_input[i]))
			count++;
		i++;
	}
	return (count);
}

bool no_skip(char c)
{	
    return (c != '\\' && c != '\n' && c != '\t' && \
        c != '\v' && c != '\f' && c != '\r' && \
        c != ';');
}

void	skip_middle_spaces(char *user_input, int *i)
{
	while (user_input[*i] && user_input[*i] == ' ')
		(*i)++;
	if (user_input[*i] != '\0')
			(*i)--;
}

char    *custom_strtrim(char *str, char c)
{
    int     start;
    int     end;
    int     len;
    int     i;
    char    *new_str;

    if (!str)
        return (NULL);
    start = 0;
    end = ft_strlen(str) - 1; // -1 para no leer desde null
    while (str[start] == c && str[start])
        start++;
    while (end > start && str[end] == c)
        end--;
    len = end - start + 1; // por quitarle -1 anteriormente
    new_str = malloc((len + 1) * sizeof(char));
    if (!new_str)
        return (NULL);
    i = 0;
    while (start <= end)
        new_str[i++] = str[start++];
    new_str[i] = '\0';
	free(str);
    return (new_str);
}
static bool check_quotes_balance(char *str)
{
    int     i;
    t_quote quote;
    
    i = 0;
    quote.type = '\0';  // Initialize quote type
    quote.closed = true;
    
    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            if (!quote.type)
            {
                quote.type = str[i];
                quote.closed = !quote.closed;
            }
            else if (str[i] == quote.type)
            {
                quote.closed = !quote.closed;
                quote.type = '\0';
            }
        }
        i++;
    }
    return (quote.closed);
}

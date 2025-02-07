/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:15:12 by antonimo          #+#    #+#             */
/*   Updated: 2025/02/07 14:23:53 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_input(t_minishell *minishell, char **envp)
{
	ft_memset(minishell, 0, sizeof(t_minishell));
	minishell->user = ft_getenv(envp, "USER=");
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

void 	parse_input(t_minishell *minishell, char **envp)
{
	minishell->user_input = clean_input(minishell);
	minishell->input_matrix = ft_split(minishell->user_input, ' ');
	print_matrix(minishell->input_matrix);
	minishell->args_num = matrixlen(minishell->input_matrix);
	minishell->cmd_path = get_path(minishell->input_matrix, envp);
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
    int	j;

    len = count_with_spaces(minishell->user_input);
    str = malloc(sizeof(char) * (len + 1));
    if (!str)
        return (NULL);
    i = 0;
    j = 0;
    while (minishell->user_input[i])
    {
        if (!ft_isspace(minishell->user_input[i])
        ||	minishell->user_input[i] == ' ')
        {
            str[j] = minishell->user_input[i];
            j++;
        }
        i++;
    }
    str[j] = '\0';
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
		if (!ft_isspace(user_input[i]) || user_input[i] == ' ')
			count++;
		i++;
	}
	return (count);
}

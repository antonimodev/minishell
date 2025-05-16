/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:15:12 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/30 14:34:28 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static bool	is_double_redir(char *str);
static bool is_single_redir(char *str);

static void	free_last_input(t_minishell *minishell)
{
	if (minishell->user_input)
	{
		free(minishell->user_input);
		minishell->user_input = NULL;
	}
}

void	get_input(t_minishell *minishell)
{
	while (!valid_rl_input(minishell))
	{
		shell_prompt(minishell);
		free_last_input(minishell);
		minishell->user_input = readline(minishell->shell_prompt);
		add_history(minishell->user_input);
		free(minishell->shell_prompt);
		minishell->shell_prompt = NULL;
	}
}

void	parse_input(t_minishell *minishell)
{
	set_expand_var(minishell);
	if (check_redir_existence(minishell))
		minishell->user_input = expand_pipe(minishell);
	char **matrix_sucia = foo_split(minishell); // debe estar en minishell
	if (minishell->redir_existence && check_valid_redir(minishell))
		handle_redir(minishell);
	else
	{
		minishell->input_matrix = split_input(minishell);
	}
	dirty_to_clean(minishell, matrix_sucia);
	minishell->args_num = matrix_len(minishell->input_matrix);
	minishell->cmd_path = get_path(minishell->input_matrix, minishell->envp);
	free_matrix(matrix_sucia); // se tendra que quitar
}

char **foo_split(t_minishell *minishell)
{
	/*
	
		conseguimos una matriz separada por espacios pero aguantando las comillas
		necesita despues de dirty_to_clean ya que necesitamos quitarle las "

	*/

	int        i;
	t_quote    quote;
	char    *word;
	char    **matrix;

	i = 0;
	quote.type = '\0';
	quote.closed = true;
	word = ft_strdup("");
	matrix = create_matrix(0);

	while (minishell->user_input[i])
	{
		quote_state(minishell->user_input[i], &quote); // e"ch"o ">>>"      hol'a'
		if (minishell->user_input[i] == ' ' && quote.closed)
		{
			skip_middle_spaces(minishell->user_input, &i);
			matrix = addmatrix(matrix, &word);
		}
		else
			word = str_append_char(word, minishell->user_input[i]);
		i++;
	}
	if (ft_strlen(word) > 0)
			matrix = addmatrix(matrix, &word);
	free(word);

	return (matrix);
}


void dirty_to_clean(t_minishell *minishell, char **matrix_sucia)
{
	int		i;

	i = 0;
	/* printf("Input matrix en dirty: \n");
	print_matrix(minishell->input_matrix);
	printf("\nMatrix sucia matrix en dirty: \n");
	print_matrix(matrix_sucia); */
	while (matrix_sucia[i])
	{
		if (is_quoted_redir_or_pipe(matrix_sucia[i]))
		{
			matrix_replace(minishell->input_matrix, i, matrix_sucia[i]);
		}
		i++;
	}
}

bool is_quoted_redir_or_pipe(char *str)
{
    char    *content;
    int     len;
    bool    result;

    if (!str || ft_strlen(str) < 3)  // Necesitamos al menos 3 caracteres: comilla+operador+comilla
        return (false);
    // Verificar si empieza y termina con comillas (dobles o simples)
    len = ft_strlen(str);
    result = false;
    if ((str[0] == '"' && str[len - 1] == '"') || (str[0] == '\'' && str[len - 1] == '\''))
    { 
        content = ft_substr(str, 1, len - 2);
        if (!content)
            return (false);
        if (new_is_redirection(content))
            result = true;
        free(content);
    }
    return (result);
}

bool	new_is_redirection(char *str)
{
        if (is_single_redir(str) || is_double_redir(str))
                return (true);
        return (false);
}

static bool	is_double_redir(char *str)
{
        if (ft_strlen(str) == 2
        && ((ft_strncmp(str, ">>", 2) == 0
        || ft_strncmp(str, "<<", 2) == 0)))
                return (true);
        return (false);
}

static bool is_single_redir(char *str)
{
        if (ft_strlen(str) == 1
        && ((ft_strncmp(str, ">", 1) == 0
        || ft_strncmp(str, "<", 1) == 0)
        || ft_strncmp(str, "|", 1) == 0))
                return (true);
        return (false);
}

/* ------------- PARSEAR PARA OBTENER MATRIZ OBJETIVO -------------*/

// EJEMPLO: echo "hola      >perro"que"" | wc ">>>" > archivo ">>" > final
/* OBJETIVO:	[echo, 
				hola     >perroque
				|
				wc
				>>>
				>
				archivo
				">>"
				>
				final]

LA MATRIX LIMPIA DEVUELVE LO QUE HAY ENTRE COMILLAS COMO UN STRING, QUITA LAS COMILLAS (ACTUALMENTE)
*/
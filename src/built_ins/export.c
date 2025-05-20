/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:09:48 by jortiz-m          #+#    #+#             */
/*   Updated: 2025/05/20 13:09:51 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_export_case(t_minishell *minishell, char *arg);
static bool find_in_matrix(char **matrix, char *var_name, int *index);

static void primer_caso(t_minishell *minishell, char *arg);

static char **apply_segundo_caso(char **matrix, char *arg, char *var_name);

static char **apply_tercer_caso(char **matrix, char *arg, char *var_name);
static char **process_found_var(char **matrix, int index, char *var_name, char *arg_value);
static char **process_new_var(char **matrix, char *arg);

static char	*insert_between_chr(char *str, char chr, int start, int end);
static int	get_chr_index(char *str, char chr);
static char *ft_strjoin_at(const char *s1, const char *s2, size_t pos);
static char	*get_envp_var_name(char *env_var);
static void show_declare_matrix(char **declare_matrix);
static char *clean_chr_from_str(char *str, char chr);

void	ft_export(t_minishell *minishell)
{
	int     i;

	i = 1;
	if (minishell->args_num == 1)
	{
		show_declare_matrix(minishell->declare_matrix);
		if (minishell->pid == CHILD)
		{
			free_minishell(minishell);
			free_matrix(minishell->envp);
			free_matrix(minishell->declare_matrix);
			exit(EXIT_SUCCESS);
		}
		return ;
	}
	while (minishell->input_matrix[i])
	{
		if (!valid_symbols(minishell->input_matrix[i])) 
		{
			printf("minishell: export: '%s': not a valid identifier\n",
				minishell->input_matrix[i]);
			minishell->exit_status = 1;
			i++;
			continue ;
		}
		handle_export_case(minishell, minishell->input_matrix[i]);
		i++;
	}
}

static void handle_export_case(t_minishell *minishell, char *arg) // perro+=jeje
{
	char	*var_name;

	var_name = get_envp_var_name(arg);
	if (!ft_strchr(arg, '='))
		primer_caso(minishell, arg);
	else
	{
		if (ft_strchr(arg, '+') && *(ft_strchr(arg, '+') + 1) == '=')
		{
			minishell->envp = apply_tercer_caso(minishell->envp, arg, var_name);
			minishell->declare_matrix = apply_tercer_caso(minishell->declare_matrix, arg, var_name);
		}
		else
		{
			minishell->envp = apply_segundo_caso(minishell->envp, arg, var_name);
			minishell->declare_matrix = apply_segundo_caso(minishell->declare_matrix, arg, var_name);
		}
	}
	free(var_name);
}

static void primer_caso(t_minishell *minishell, char *arg)
{
	int index;

	if (find_in_matrix(minishell->declare_matrix, arg, &index))
	{
		//printf("export PRIMER CASO: %s: ya existía\n", arg); // debug
		return;
	}
	minishell->declare_matrix = matrix_append(minishell->declare_matrix, arg);
	//printf("export PRIMER CASO: %s: se ha exportado\n", arg); // debug
}

static char *clean_chr_from_str(char *str, char chr) // cambiar nombre a: export_rm_chr
{
	char	*new_str;
	bool	copy;
	int		i;
	int		j;

	new_str = malloc((ft_strlen(str) + 1) * sizeof(char));
	i = 0;
	j = 0;
	copy = false;
	while(str[i])
	{
		if (str[i] != chr || copy)
		{
			new_str[j] = str[i];
			j++;
		}
		if (str[i] == chr)
			copy = true;
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

/* utils */
static char	*insert_between_chr(char *str, char chr, int start, int end) // MODULARIZAR
{
    char	*new_str;
    int		len;
    int		i;
    int		j;

	i = 0;
	j = 0;
    len = ft_strlen(str);
    new_str = malloc((len + 3) * sizeof(char));
    if (!new_str)
        return (NULL);
    if (end >= len)
        end = len + 2;
    if (end < start)
        end = start;
    while(i <= len)
    {
		if (i < len)
			new_str[j++] = str[i];
		if (i == start)
			new_str[j++] = chr;
		if (i == end)
			new_str[j++] = chr;
		i++;
    }
    new_str[j] = '\0';
    return (new_str);
}

static int	get_chr_index(char *str, char chr)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == chr)
			break ;
		i++;
	}
	return (i);
}

static char *ft_strjoin_at(const char *s1, const char *s2, size_t pos)
{
    size_t  len1;
    size_t  len2;
    char    *new_str;

    len1 = (size_t)ft_strlen(s1);
    len2 = (size_t)ft_strlen(s2);
    if (pos > len1)
        pos = len1;
    new_str = malloc(len1 + len2 + 1);
    if (new_str == NULL)
        return (NULL);
    ft_memcpy(new_str, s1, pos);
    ft_memcpy(new_str + pos, s2, len2);
    ft_memcpy(new_str + pos + len2, s1 + pos, len1 - pos);
    new_str[len1 + len2] = '\0';
    return (new_str);
}

static char	*get_envp_var_name(char *env_var)
{
	char	*var_name;
	int		i;

	i = 0;
	while (env_var[i] && env_var[i] != '+' && env_var[i] != '=')
		i++;
	var_name = ft_substr(env_var, 0, i);
	return (var_name);
}

static void show_declare_matrix(char **declare_matrix) // para modificar el original de minishell->declare_matrix[i]
{
	int		i;
	int		pos;
	char	*new_str;
	char	**matrix_copy;

	i = 0;
	matrix_copy = matrix_cpy(declare_matrix, 0);
	while(matrix_copy[i])
	{
		pos = get_chr_index(matrix_copy[i], '=');
		if (pos != (int)ft_strlen(matrix_copy[i]) && matrix_copy[i][pos + 1] != '"')
		{
			new_str = insert_between_chr(matrix_copy[i], '"', pos, ft_strlen(matrix_copy[i]) - 1);
			free(matrix_copy[i]);
			matrix_copy[i] = ft_strdup(new_str);
			free(new_str);
		}
		printf("declare -x %s\n", matrix_copy[i]);
		i++;
	}
	free_matrix(matrix_copy);
}

/***************************** TESTING ************************** */


static bool find_in_matrix(char **matrix, char *var_name, int *index)
{
    *index = 0;
    while (matrix && matrix[*index])
    {
        if (!ft_strncmp(matrix[*index], var_name, ft_strlen(var_name)) && 
            (matrix[*index][ft_strlen(var_name)] == '=' || 
             matrix[*index][ft_strlen(var_name)] == '\0'))
            return (true);
        (*index)++;
    }
    return (false);
}

static char **apply_segundo_caso(char **matrix, char *arg, char *var_name)
{
	int     index;
	bool    found;

	found = find_in_matrix(matrix, var_name, &index);
	if (found)
	{
		matrix_replace(matrix, index, arg);
		//printf("export SEGUNDO CASO %s: se ha reemplazado\n", arg); // debug
	}
	else
	{
		matrix = matrix_append(matrix, arg);
		//printf("export SEGUNDO CASO %s: se ha añadido\n", arg); // debug
	}
    return (matrix);
}

static char **apply_tercer_caso(char **matrix, char *arg, char *var_name)
{
	int     index;
	bool    found;
	char    *arg_value;
	// Extraer el valor después del '='
	arg_value = ft_substr(arg, get_chr_index(arg, '=') + 1, 
							ft_strlen(arg) - get_chr_index(arg, '='));
	printf("arg_value en += %s\n", arg_value);
	found = find_in_matrix(matrix, var_name, &index);
	if (found)
		matrix = process_found_var(matrix, index, var_name, arg_value);
	else
		matrix = process_new_var(matrix, arg);
	free(arg_value);
	return (matrix);
}

static char **process_found_var(char **matrix, int index, char *var_name, char *arg_value) // PWD+=jiji
{
	char *value_ptr;
	char *temp_str;
	char *temp_str2;
	char *final_str;

	// Obtenemos el valor original después del '='
	value_ptr = matrix[index] + ft_strlen(var_name);
	if (*value_ptr == '=')
		value_ptr++;
	// Concatenar el nuevo valor al existente
	temp_str = ft_strjoin_at(value_ptr, arg_value, ft_strlen(value_ptr));
	temp_str2 = ft_strjoin(var_name, "=");
	final_str = strjoin_and_free(temp_str2, temp_str);
	free(temp_str);
	matrix_replace(matrix, index, final_str);
	//printf("export TERCER CASO: %s: se ha reemplazado\n", final_str);
	free(final_str);
	return (matrix);
}

static char **process_new_var(char **matrix, char *arg)
{
	char *arg_modified;
	
	arg_modified = clean_chr_from_str(arg, '+');
	matrix = matrix_append(matrix, arg_modified);
	//printf("export TERCER CASO: %s: se ha añadido\n", arg_modified);
	free(arg_modified);
	return (matrix);
}
/*
CASOS:

export PERRO
export PERRO=
export PERRO=valor
export PERRO=valor1 GATO=valor2
export PERRO+=
export PERRO+=valor
export PERRO+=valor1 GATO=valor2

{
	NO DEBE DUPLICARSE
	export perro
	export perro=jeje
	---
	export perro
	export perro+=jeje
}
*/
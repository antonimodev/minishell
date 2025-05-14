#include "minishell.h"

static void handle_export_case(t_minishell *minishell, char *arg);
static char	*get_envp_export(char **envp, char *env_var, int *envp_index);
static void primer_caso(t_minishell *minishell, char *arg);
static void segundo_caso(t_minishell *minishell, char *arg, char *var_name);
static void segundo_caso_declare_x(t_minishell *minishell, char *arg, char *var_name);
static void tercer_caso(t_minishell *minishell, char *arg, char *var_name);
static char	*insert_between_chr(char *str, char chr, int start, int end);
static int	get_chr_index(char *str, char chr);
static char *ft_strjoin_at(const char *s1, const char *s2, size_t pos);
static char	*get_envp_var_name(char *env_var);
static void show_declare_matrix(char **declare_matrix);
//static char	*chr_between_str(char *str1, char *chr, char *str2);

// DEBEMOS GUARDAR MINISHELL->DECLARE_MATRIX EN INIT_MINISHELL IGUAL QUE
// LO HACEMOS CON ENV

void	ft_export2(t_minishell *minishell) // "perro" "gato=" "perro+="
{
	int     i;
	char    **args;

	i = 0;
	if (minishell->args_num == 1)
	{
		show_declare_matrix(minishell->declare_matrix);
		return ;
	}
	args = matrix_from_matrix(minishell->input_matrix, 1,
		matrix_len(minishell->input_matrix));
	while (args[i])
	{
		handle_export_case(minishell, args[i]);
		i++;
	}
	free_matrix(args);
}

static void handle_export_case(t_minishell *minishell, char *arg) // perro+=jeje
{
	char	*var_name;

	var_name = get_envp_var_name(arg);
	printf("arg: %s\n", var_name);
	if (!ft_strchr(arg, '='))
		primer_caso(minishell, arg);
	else
	{
		if (ft_strchr(arg, '+') && *(ft_strchr(arg, '+') + 1) == '=')
			tercer_caso(minishell, arg, var_name);
		else
		{
			segundo_caso(minishell, arg, var_name);
			segundo_caso_declare_x(minishell, arg, var_name);
		}
	}
	free(var_name);
}

static char	*get_envp_export(char **envp, char *env_var, int *envp_index)
{
	int	len;

	len = ft_strlen(env_var);
	while (envp[*envp_index])
	{
		// Verifica que la longitud coincide o que el siguiente carácter sea '='
		if (!ft_strncmp(envp[*envp_index], env_var, len) && 
			(envp[*envp_index][len] == '=' || envp[*envp_index][len] == '\0'))
			return (envp[*envp_index] + len);
		(*envp_index)++;
	}
	return (NULL);
}

static void primer_caso(t_minishell *minishell, char *arg) // if "PERRO"
{
	char	*envp_pointer;
	int		envp_index;

	envp_index = 0;
	while (minishell->declare_matrix[envp_index])
	{
		envp_pointer = get_envp_export(minishell->declare_matrix, arg, &envp_index);
		printf("primer caso: envp_pointer: %s\n", envp_pointer); // debug
		if (envp_pointer) // primer caso "PERRO"
			return ;
	}
	minishell->declare_matrix = matrix_append(minishell->declare_matrix, arg);
	printf("export PRIMER CASO: %s: se ha exportado\n", arg); // debug
}

static void segundo_caso(t_minishell *minishell, char *arg, char *var_name) // if "PERRO="
{
	int		envp_index;
	char	*envp_pointer;

	envp_index = 0;
	while(minishell->envp[envp_index])
	{
		envp_pointer = get_envp_export(minishell->envp, var_name, &envp_index);
		if (envp_pointer)
		{
			matrix_replace(minishell->envp, envp_index, arg);
			printf("export SEGUNDO CASO: %s: se ha reemplazado\n", arg); // debug
			return ;
		}
	}
	minishell->envp = matrix_append(minishell->envp, arg);
	printf("export SEGUNDO CASO: %s: se ha añadido\n", arg); // debug
}

static void segundo_caso_declare_x(t_minishell *minishell, char *arg, char *var_name) // export PERRO=valor
{
    char    *arg_modified;
    int     start;
    int     envp_index;

    start = get_chr_index(arg, '=');
    envp_index = 0;
    while (minishell->declare_matrix[envp_index])
    {
		if (get_envp_export(minishell->declare_matrix, var_name, &envp_index))
		{
			arg_modified = insert_between_chr(arg, '"', start, ft_strlen(arg) - 1);
			if (!arg_modified)
				return ;
			matrix_replace(minishell->declare_matrix, envp_index, arg_modified);
			printf("export SEGUNDO CASO DECLARE -X: %s: se ha reemplazado\n", arg_modified); // debug
			free(arg_modified);
			return ;
		}
	}
	arg_modified = insert_between_chr(arg, '"', start, ft_strlen(arg) - 1); // export perro= -> perro=""
	if (!arg_modified)
		return;
	minishell->declare_matrix = matrix_append(minishell->declare_matrix, arg_modified);
	printf("export SEGUNDO CASO DECLARE -X: %s: se ha añadido\n", arg_modified); // debug
	free(arg_modified);
}

static void tercer_caso(t_minishell *minishell, char *arg, char *var_name) // if PERRO+=webo // PERRO="pepe"
{
	int		envp_index;
	char	*envp_pointer;
	char	*arg_value;
	char	*arg_modified;

	envp_index = 0;
	arg_value = ft_substr(arg, get_chr_index(arg, '=') + 1, ft_strlen(arg) - get_chr_index(arg, '='));
	printf("arg_value: %s\n", arg_value);
	while (minishell->envp[envp_index])
	{
		envp_pointer = get_envp_export(minishell->envp, var_name, &envp_index);
		printf("env_pointer: %s\n", envp_pointer); // debug
		if (envp_pointer)
		{
			arg_modified = ft_strjoin_at(envp_pointer, arg_value, ft_strlen(envp_pointer));
			arg_modified = ft_strjoin(var_name, arg_modified);
			matrix_replace(minishell->envp, envp_index, arg_modified);
			printf("export TERCER CASO: %s: se ha reemplazado\n", arg_modified); // debug
			free(arg_modified);
			return;
		}
	}
}

/* static char	*chr_between_str(char *str1, char *chr, char *str2)
{
	char	*new_str;

	new_str = ft_strdup("");
	new_str = strjoin_and_free(new_str, str1);
	printf("str1: %s\n", new_str);
	new_str = strjoin_and_free(new_str, chr);
	printf("str1 + chr: %s\n", new_str);
	new_str = strjoin_and_free(new_str, str2);
	printf("new_str terminado: %s\n", new_str);
	return (new_str);
} */

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
		if (pos != (int)ft_strlen(matrix_copy[i]))
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

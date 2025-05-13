#include "minishell.h"

static void handle_export_case(t_minishell *minishell, char *arg);
static char	*get_envp_export(char **envp, char *env_var, int *envp_index);
static void primer_caso(t_minishell *minishell, char *arg);
static void segundo_caso(t_minishell *minishell, char *arg);
static void segundo_caso_declare_x(t_minishell *minishell, char *arg);
static void tercer_caso(t_minishell *minishell, char *arg);
static char	*insert_between_chr(char *str, char chr, int start, int end);
static int	get_chr_index(char *str, char chr);
static char *ft_strjoin_at(const char *s1, const char *s2, size_t pos);

void	ft_export2(t_minishell *minishell) // "perro" "gato=" "perro+="
{
	int     i;
	char    **args;

	i = 0;
	minishell->declare_matrix = matrix_cpy(minishell->envp, 0);
	printf("ARGS NUM: %d\n", minishell->args_num); // debug
	if (minishell->args_num == 1)
	{
		while(minishell->declare_matrix[i])
		{
			printf("declare -x %s\n", minishell->declare_matrix[i]);
			i++;
		}
		return ;
	}
	args = matrix_from_matrix(minishell->input_matrix, 1,
		matrix_len(minishell->input_matrix) - 1);

	print_matrix(args); // debug
	while (args[i])
	{
		handle_export_case(minishell, args[i]);
		i++;
	}
	free_matrix(args);
}

static void handle_export_case(t_minishell *minishell, char *arg)
{
	
	if (ft_strchr(arg, '='))
		primer_caso(minishell, arg);
	else
	{
		if (ft_strchr(arg, '+') && *(ft_strchr(arg, '+') + 1) == '=')
			tercer_caso(minishell, arg);
		else
		{
			segundo_caso(minishell, arg);
			segundo_caso_declare_x(minishell, arg);
		}
	}
}

static char	*get_envp_export(char **envp, char *env_var, int *envp_index)
{
	int	len;

	len = ft_strlen(env_var);
	while (envp[*envp_index])
	{
		if (!ft_strncmp(envp[*envp_index], env_var, len))
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
		if (!envp_pointer[0]) // primer caso "PERRO"
			return ;
		envp_index++;
	}
	matrix_append(minishell->declare_matrix, arg);
	printf("export PRIMER CASO: %s: se ha exportado\n", arg); // debug
}

static void segundo_caso(t_minishell *minishell, char *arg) // if "PERRO="
{
	int		envp_index;
	char	*envp_pointer;

	envp_index = 0;
	while(minishell->envp[envp_index])
	{
		envp_pointer = get_envp_export(minishell->envp, arg, &envp_index);
		if (envp_pointer[0] == '=')
		{
			matrix_replace(minishell->declare_matrix, envp_index, arg);
			printf("export SEGUNDO CASO: %s: se ha reemplazado\n", arg); // debug
			return ;
		}
		envp_index++;
	}
	matrix_append(minishell->declare_matrix, arg);
	printf("export SEGUNDO CASO: %s: se ha exportado\n", arg); // debug
}

static void segundo_caso_declare_x(t_minishell *minishell, char *arg) // export PERRO=valor
{
	char	*arg_modified;
	char	*envp_pointer;
	int		start;
	int		envp_index;

	start = get_chr_index(arg, '=') + 1;
	envp_index = 0;
	while (minishell->declare_matrix[envp_index])
	{
		envp_pointer = get_envp_export(minishell->declare_matrix, arg, &envp_index);
		if (!envp_pointer[0] || envp_pointer[0] == '=')
		{
			arg_modified = insert_between_chr(minishell->declare_matrix[envp_index], '"', start, ft_strlen(arg));	
			matrix_replace(minishell->declare_matrix, envp_index, arg_modified);
			printf("export SEGUNDO CASO: %s: se ha reemplazado\n", arg); // debug
			free(arg_modified);
			return ;
		}
		envp_index++;
	}
}

static void tercer_caso(t_minishell *minishell, char *arg) // if PERRO+=webo // PERRO="pepe"
{
	int		envp_index;
	char	*envp_pointer;
	char	*arg_value;
	char	*concat_str;
	char	*arg_modified;

	envp_index = 0;
	while (minishell->declare_matrix[envp_index])
	{
		envp_pointer = get_envp_export(minishell->declare_matrix, arg, &envp_index);
		if (envp_pointer[0] == '=')
		{
			arg_value = ft_strchr(arg, '=') + 1;
			concat_str = ft_strjoin_at(minishell->declare_matrix[envp_index], arg_value, ft_strlen(minishell->declare_matrix[envp_index] - 2));
			matrix_replace(minishell->declare_matrix, envp_index, concat_str);
			printf("export TERCER CASO: %s: se ha reemplazado\n", arg); // debug
			free(concat_str);
			return ;
		}
		envp_index++;
	}
	arg_modified = insert_between_chr(minishell->declare_matrix[envp_index], '"', get_chr_index(arg, '=') + 1, ft_strlen(arg));
	matrix_replace(minishell->declare_matrix, envp_index, arg_modified);
	printf("export TERCER CASO: %s: se ha reemplazado\n", arg); // debug
	free(arg_modified);
}

/* utils */
static char	*insert_between_chr(char *str, char chr, int start, int end)
{
	char	*new_str;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(str) + 3;
	new_str = malloc(sizeof(char) * len);
	if (!new_str)
		return (NULL);
	while(str[i])
	{
		if (i == start)
			new_str[j++] = chr;
		new_str[j] = str[i];
		i++;
		j++;
		if (i == end + 1)
			new_str[j++] = chr;
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

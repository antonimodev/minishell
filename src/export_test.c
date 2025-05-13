#include "minishell.h"

/* typedef enum e_export_cases
{
	NONE,
	EQUAL,
	PLUS_EQUAL,
} e_export_cases; */

static void	export(t_minishell *minishell) // "perro" "gato=" "perro+="
{
	int     i;
	int     j;
	char    **declare_matrix;
	char    **args;

	i = 0;
	j = 0;
	declare_matrix = matrix_cpy(minishell->envp, 0);
	args = matrix_from_matrix(minishell->input_matrix, 1,
		matrix_len(minishell->input_matrix) - 1);
	while (args[i])
	{
		handle_export_case(minishell, args[i]);
		i++;
	}
}

static void handle_export_case(t_minishell *minishell, char *arg)
{
	char *equal_sign;
	char *plus_sign;

	equal_sign = ft_strchr_gnl(arg, '=');
	if (!equal_sign)
		primer_caso(minishell, arg);
	else
	{
		plus_sign = ft_strchr_gnl(arg, '+');
		if (plus_sign && plus_sign + 1 == equal_sign)
			tercer_caso(minishell, arg);
		else
			segundo_caso(minishell, arg);
	}
}

char	*foo_envp(char **envp, char *env_var, int *envp_index)
{
	int	len;

	len = ft_strlen(env_var);
	while (envp[envp_index])
	{
		if (!ft_strncmp(envp[envp_index], env_var, len))
			return (envp[envp_index] + len);
		envp_index++;
	}
	return (NULL);
}

static void primer_caso(t_minishell *minishell, char *arg) // if "PERRO"
{
	char	*env_pointer;
	int		envp_index;

	envp_index = 0;
	while (declare_matrix[envp_index])
	{
		envp_pointer = foo_envp(declare_matrix[envp_index], arg, &envp_index);
		if (!envp_pointer[0]) // primer caso "PERRO"
			return ;
		envp_index++;
	}
	matrix_append(declare_matrix, arg);
}

static void segundo_caso(t_minishell *minishell, char *arg) // if "PERRO="
{
	int		envp_index;
	char	*envp_pointer;

	envp_index = 0;
	while(minishell->envp[envp_index])
	{
		envp_pointer = foo_envp(minishell->envp, arg, envp_index);
		if (envp_pointer[0] == '=')
			// MATRIX_PRINCIPAL = matrix_replace para sustituir contenido existente
		envp_index++;
	}
	// MATRIX_APPEND = se añade debido a que no existe en la MATRIX_PRINCIPAL
}
static void segundo_caso_declare_x(t_minishell *minishell, char *arg)
{
	char	*arg_modified;
	int		start;
	int		i;

	start = get_chr_index(arg, '=');
	start++;
	i = 0;
	while (declare_matrix[envp_index])
	{
		envp_pointer = foo_envp(declare_matrix[i], arg[i], envp_index);
		if (!envp_pointer[0] || envp_pointer[0] == '=')
		{
			arg_modified = insert_between_chr(arg[i], '"', start, ft_strlen(arg[i])); // no se si es strchr para buscar el indice start
			// matrix_replace(declare_matrix, arg_modified);
			// free(arg_modified);
			// return ;
		}
		envp_index++;
	}
}


/* utils */
char	*insert_between_chr(char *str, char chr, int start, int end)
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
int		get_chr_index(char *str, char chr)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == chr)
			return (i);
		i++;
	}
}
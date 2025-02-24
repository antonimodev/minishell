#include "minishell.h"

void ft_export(t_minishell *minishell)
{
    int i;

    // Si hay más de 2 argumentos (export arg1 arg2...)
    if (minishell->args_num > 2)
    {
        write(1, "\n", 1);
        return;
    }
    // Si hay exactamente 2 argumentos (export VAR=VALUE)
    if (minishell->args_num == 2)
    {
        /*
		Nombres de variables NO VÁLIDOS (y por qué):
		hola-! (guion - y signo de exclamación !)
		mi-variable (guion -)
		1variable (empieza con un número)
		variable espacio (contiene un espacio)
		variable.punto (contiene un punto .)
		variable+mas (contiene un signo +)
		variable$dolar (contiene un signo $)
		variable#almohadilla (contiene una almohadilla #)
		
		funcion que cribe esos simbolos hasta que se encuentre "="*/
		if (validar_simbolos(minishell->input_matrix[1]))
        	minishell->envp = matrix_append(minishell->envp, minishell->input_matrix[1]);
		printf("%s not a valid identifier\n", minishell->input_matrix[1]);
        return;
    }
    // Si solo es "export" muestra todas las variables
    i = 0;
    while (minishell->envp[i])
    {
        printf("declare -x %s\n", minishell->envp[i]);
        i++;
    }
}

bool	validar_simbolos(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == caracter chungo)
			return (false);
		i++;
	}
	return (true);
}

char	**matrix_append(char **matrix, char *new_str)
{
	char	**new_matrix;
	int		len;
	
	new_matrix = matrix_cpy(matrix, 1);
	if (!new_matrix)
		return (NULL);
	len = matrixlen(matrix);
	new_matrix[len] = ft_strdup(new_str);
	if (!new_matrix[len])
	{
		free_matrix_error(new_matrix, len);
		return (NULL);
	}
	free_matrix(matrix);
	return (new_matrix);
}

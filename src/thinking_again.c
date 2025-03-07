#include "minishell.h"

/*

	echo "'hola''$HOME'"

	Recorremos str haciendo quote_balance concatenando todo el input

	Una vez que encontremos $, empezamos a concatenar en un word hasta que encontremos un caracter delimitante

	Ya con el word formado, buscamos con getenv si existe, si da resultado, comprobamos que quote.type hay actualmente.
	Si este quote.type es ", podemos hacer la expansion y sustituimos desde el $ con la expansion de la var.
	Si es tipo ', no podemos hacer la expansion.

	Si resulta que no ha encontrado nada con el getenv, concatenamos el $NO_EXIST con el str del input y ea.
*/

void	quote_status(t_quote *quote, char c)
{
	if (c == '"' || c == '\'')
	{
		if (!quote->type)
		{
			quote->type = c;
			quote->closed = !quote->closed;
		}
		else if (c == quote->type)
		{
			quote->closed = !quote->closed;
			quote->type = '\0';
		}
	}
}

void mount_env(char *user_input, char *env_var, unsigned int i)
{
	// VAMOS A MONTAR LA VARIABLE DE ENTORNO
	while (user_input[i] && user_input[i] != ' ') // hasta encontrar un char delimitante ( igual hay mas delimitantes )
	{
		// MONTAMOS ENV_VAR
		env_var = str_append_char(env_var, user_input[i]);
		i++;
	}
}

void	add_env(char *expanded_str, char *env_var, unsigned int *i)
{
	expanded_str = ft_strjoin_gnl(expanded_str, env_var);
	*i += (ft_strlen_gnl(env_var) - 1); // igual es -2, hay que debugar
}

void valid_env(t_minishell *minishell, char *env_var, char *expanded_str, unsigned int *i)
{
	char *exist_env;

	// BUSCAMOS ENV_VAR MONTADO EN FT_GETENV
	exist_env = ft_getenv(minishell->envp, env_var);
	if (exist_env)
		add_env(expanded_str, env_var, i);
	else
		expanded_str = str_append_char(expanded_str, '$');
}

void	process_env(t_minishell *minishell, unsigned int *i, t_quote *quote, char	*expanded_str)
{
	char *env_var;

	env_var = ft_strdup("");
	// EL CARACTER ACTUAL ES $?
	if (minishell->user_input[*i] == '$' && quote->type != '\'')
	{
		mount_env(minishell->user_input ,env_var, *i);
		valid_env(minishell, env_var, expanded_str, i);		
	}
	else	// NO ES $? -> concatenar el char actual
		expanded_str = str_append_char(expanded_str, minishell->user_input[*i]);
	free(env_var);
}

void expand_env(t_minishell *minishell)
{
	char			*expanded_str;
	t_quote			quote;
	unsigned int	i;

	expanded_str = ft_strdup("");
	quote.type = '\0';
	quote.closed = true;
	i = 0;

	while(minishell->user_input[i])
	{
		quote_status(&quote, minishell->user_input[i]);
		process_env(minishell, &i, &quote, expanded_str);
		i++;
	}
	minishell->user_input = ft_strjoin_gnl(minishell->user_input, expanded_str);
	free(expanded_str);
}

#include "minishell.h"

char    *get_path(char **cmd, char **envp)
{
    char	*path;
	char	**path_split;
	char	*filepath;

    path = get_env(envp, "PATH="); //path ahora apunta a la variable de entorno PATH
	path_split = ft_split(path, ':'); // usr/bin:bin -> usr/bin, bin
	concat_path(path_split, cmd[0]); // concatena comando, /usr/bin -> /usr/bin/ls
	filepath = get_cmd(path_split); // devuelve el primer filepath que exista (usr/bin/ls)
    free_matrix(path_split); // liberamos path_split que fue utilizado para buscar el filepath
    return (filepath); // return usr/bin/ls
}

char    *get_env(char **envp, char *env_var)
{
    int i;
    int len;
    
    i = 0;
    len = ft_strlen(env_var);
    while (envp[i])
    {
        if (ft_strncmp(envp[i], env_var, len) == 0)
            return (envp[i] + len);
        i++;
    }
    return (NULL);
}

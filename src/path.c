#include "minishell.h"

char    *get_path(char **cmd, char **envp)
{
    char	*path;
	char	**path_split;
	char	*filepath;

    path = get_env(envp, "PATH=");
	path_split = ft_split(path, ':');
	cmd_path(path_split, cmd[0]);
	filepath = get_cmd(path_split);
    free_matrix(path_split);
    return (filepath);
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

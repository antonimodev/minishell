#include "minishell.h"

char	**set_raw(char **envp)
{
	char	*raw_env;
	char    **splitted_paths;

    raw_env = ft_getenv(envp, "PATH=");
	splitted_paths = ft_split(raw_env, ':');
    return(splitted_paths);
}


char    *get_path(char **input_matrix, char **envp)
{
	char	*cmd_path;
    char    **splitted_paths;

	cmd_path = NULL;
	splitted_paths = set_raw(envp);
    concat_paths(splitted_paths, input_matrix[0]);
	get_cmd_path(splitted_paths, &cmd_path);
	printf("cmd_path: %s\n", cmd_path);
    free_matrix(splitted_paths);
    return (cmd_path);
}

char    *ft_getenv(char **envp, char *env_var)
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

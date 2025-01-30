#include "minishell.h"
	// OPCIONAL
	//comprobar strchr de "/", comprobar con stat y si es true, return strdup(cmd)
	//utilizar stat() en caso de que sea ruta relativa
	//usar access(F_OK, X_OK) para existencia y permisos

void	execute(char *cmd)
{
	char	*path;
	char	**path_split;

	//si me pasan ruta con "/" comprobar directamente
	path = getenv("PATH");
	path_split = ft_split(path, ':');
	cmd_path(path_split, cmd);
	if (!check_cmd(path_split))
	{
		// posiblemente aqui venga un mensaje de que cmd_path no existe
		printf("minishell: %s: command not found\n", cmd);
		free_matrix(path_split);
		return ;
	}
	printf("GUCCI\n");
	//funcion de fork y execve
	free_matrix(path_split);
}

void	cmd_path(char **path_split, char *cmd)
{
	int		i;

	i = 0;
	while (path_split[i])
	{
		path_split[i] = cmdcat(path_split[i], cmd);
		i++;
	}
}

char	*cmdcat(char *path, char *cmd)
{
	char	*filepath;
	int		path_len;
	int		cmd_len;

	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	filepath = malloc (path_len + cmd_len + 2 * sizeof(char)); // para "/" y "\0"
	if (!filepath)
		return (NULL);
	filepath = ft_strcpy(filepath, path);
	filepath = ft_strcat(filepath, "/");
	filepath = ft_strcat(filepath, cmd);
	free(path);
	return (filepath);
}

bool	check_cmd(char **path_split)
{
	int			i;

	i = 0;
	while (path_split[i])
	{
		if (is_valid(path_split[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	is_valid(char *cmd_path)
{
    struct stat	buffer;

    if (access(cmd_path, F_OK | X_OK)
        || stat(cmd_path, &buffer)
        || !S_ISREG(buffer.st_mode)
        || !(buffer.st_mode & S_IXUSR))
    {
        return (false);
    }
    return (true);
}

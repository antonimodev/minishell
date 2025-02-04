#include "minishell.h"
	// OPCIONAL
	//comprobar strchr de "/", comprobar con stat y si es true, return strdup(cmd)
	//utilizar stat() en caso de que sea ruta relativa
	//usar access(F_OK, X_OK) para existencia y permisos
	//si me pasan ruta con "/" comprobar directamente

void	execute(t_input *input, char **envp)
{
	char	*filepath;

	input->input_matrix = ft_split(input->user_input, ' ');

	filepath = get_path(input->input_matrix, envp);
	if (not_found(filepath, input->input_matrix))
		return ;
	fork_exec(filepath, input->input_matrix, envp);
	free(filepath);
}

bool not_found(char *filepath, char **input_matrix)
{
	if(!filepath)
	{
		printf("minishell: %s: command not found\n", input_matrix[0]);
		return true;
	}
	return false;
}

void	concat_paths(char **path_split, char *cmd)
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
	filepath = malloc ((path_len + cmd_len + 2) * sizeof(char)); // para "/" y "\0"
	if (!filepath)
		return (NULL);
	filepath = ft_strcpy(filepath, path);
	filepath = ft_strcat(filepath, "/");
	filepath = ft_strcat(filepath, cmd);
	free(path);
	return (filepath);
}

char 	*get_cmd_path(char **splitted_paths, char **cmd_path)
{
	int	i;

	i = 0;
	while (splitted_paths[i])
	{
		if (is_valid(splitted_paths[i]))
		{
			(*cmd_path) = ft_strdup(splitted_paths[i]);
			return (*cmd_path);
		}
		i++;
	}
	return (NULL);
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

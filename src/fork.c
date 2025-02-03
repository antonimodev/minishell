#include "minishell.h"

// Hacer funcion que haga fork y execve del comando con flags y argumentos
void	fork_exec(char *cmd_path, char **cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, cmd, envp) != 0)
		{
			free(cmd_path);
			free_matrix(cmd);
			printf("%s: invalid line with: ", cmd[1]);
		}
	}
	else
		waitpid(pid, NULL, 0);
}

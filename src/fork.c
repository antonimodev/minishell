#include "minishell.h"

// Hacer funcion que haga fork y execve del comando con flags y argumentos
void	fork_exec(char *cmd_path, //matrix of args)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (!execve(cmd_path, args, NULL));
		{
		}
}

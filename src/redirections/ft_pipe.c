#include "minishell.h"

/* void	ft_pipe(t_minishell)
{
	if ()
	fd_redirection(STDIN_FILENO, fd);
	fd_redirection(STDOUT_FILENO, pipe.write_pipe);
	close(pipe.read_pipe);
	close(pipe.write_pipe);
} */

void	fd_redirection(int from, int to)
{
	if (dup2(to, from) == -1)
	{
		perror("dup2: error duplicating fd");
		exit(EXIT_FAILURE);
	}
}

void ft_pipe(t_minishell *minishell)
{
    if (minishell->first_cmd == 1)
    {
        // First command writes to pipe
        fd_redirection(STDOUT_FILENO, minishell->pipe.write_pipe);
        
        // Only close the read end that this process won't use
        close(minishell->pipe.read_pipe);
        
        // DON'T close write_pipe here - the command needs to write to it
        // The descriptor will be closed automatically when the process exits
    }
    else if (minishell->first_cmd != 1)
    {
        // Second command reads from pipe
        fd_redirection(STDIN_FILENO, minishell->pipe.read_pipe);
        
        // Only close the write end that this process won't use
        close(minishell->pipe.write_pipe);
        
        // DON'T close read_pipe here - the command needs to read from it
        // The descriptor will be closed automatically when the process exits
    }
}

/*
Probablemente hagamos una funcion en la que comprobemos en handle_operator si el operador es PIPE
en el caso de que lo sea, tendremos un contador i = 0 y haremos i++, comprobar que esa i == 1, para
activar la flag minishell->first_cmd, y si es != 1, entonces se desactiva.
*/
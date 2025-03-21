#include "minishell.h"

void	ft_pipe(t_minishell)
{
	if ()
	fd_redirection(STDIN_FILENO, fd);
	fd_redirection(STDOUT_FILENO, pipe.write_pipe);
	close(pipe.read_pipe);
	close(pipe.write_pipe);
}


void ft_pipe(t_minishell *minishell, int pipe_fd[2])
{
    // For the first command (writes to pipe)
    if (minishell->redirection == PIPE && minishell->first_cmd)
    {
        // First command reads from stdin (default)
        // First command writes to pipe
        fd_redirection(STDOUT_FILENO, pipe_fd[1]);
        close(pipe_fd[0]); // Close unused read end
    }
    // For the second command (reads from pipe)
    else if (minishell->redirection == PIPE && !minishell->first_cmd)
    {
        // Second command reads from pipe
        fd_redirection(STDIN_FILENO, pipe_fd[0]);
        // Second command writes to stdout (default)
        close(pipe_fd[1]); // Close unused write end
    }
}

/*
Probablemente hagamos una funcion en la que comprobemos en handle_operator si el operador es PIPE
en el caso de que lo sea, tendremos un contador i = 0 y haremos i++, comprobar que esa i == 1, para
activar la flag minishell->first_cmd, y si es != 1, entonces se desactiva.
*/
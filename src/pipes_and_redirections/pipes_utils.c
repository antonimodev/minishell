#include "minishell.h"

void	count_operators(t_minishell *minishell) // probablemente pipe_utils.c
{
	minishell->first_cmd++;
}

void	redirect(t_minishell *minishell)
{
	// Si quieres imprimir el contenido como debug, hazlo así:
	if (minishell->redirection == PIPE)
		ft_pipe(minishell);
/* 	else if (minishell->redirection == REDIR_IN)
		ft_redir_in();
	else if (minishell->redirection == REDIR_OUT)
		ft_redir_out();
	else if (minishell->redirection == REDIR_APPEND)
		ft_redir_append();
	else if (minishell->redirection == REDIR_HEREDOC)
		ft_redir_heredoc(); */
}

void	store_pipes(t_minishell *minishell)
{
	minishell->pipes.STDIN = dup(STDIN_FILENO);
	minishell->pipes.STDOUT = dup(STDOUT_FILENO);
}

void	reset_pipes(t_minishell *minishell)
{
    if (minishell->redirection)
    {
        fd_redirection(STDIN_FILENO, minishell->pipes.STDIN);
        fd_redirection(STDOUT_FILENO, minishell->pipes.STDOUT);
        close(minishell->pipes.STDIN);
        close(minishell->pipes.STDOUT);
    }
}
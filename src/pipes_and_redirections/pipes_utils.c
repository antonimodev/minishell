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

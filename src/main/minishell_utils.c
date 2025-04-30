/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:50:46 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/30 11:24:29 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(t_minishell *minishell, char **envp)
{
	update_minishell(minishell, envp);
	store_fd(minishell);
	minishell->pid = PARENT;
	minishell->user = ft_getenv(minishell->envp, "USER=");
	minishell->user_input = ft_strdup("");
}

char	*ft_getenv(char **envp, char *env_var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(env_var);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], env_var, len))
			return (envp[i] + len);
		i++;
	}
	return (NULL);
}

void	free_minishell(t_minishell *minishell)
{
	if (minishell->user_input)
		free(minishell->user_input);
	if (minishell->cmd_path)
		free(minishell->cmd_path);
	if (minishell->input_matrix)
		free_matrix(minishell->input_matrix);
	if (minishell->shell_prompt)
		free(minishell->shell_prompt);
	if (minishell->pipe_tools.pipes)
		free(minishell->pipe_tools.pipes);
}

// suggest
void	print_minishell(t_minishell *minishell)
{
    int	i;
    
    fprintf(stderr, "\n\033[1;36m=== MINISHELL PID:%d INFO ===\033[0m\n\n",
        minishell->pid);
    fprintf(stderr, "\033[1m▶ Process type:\033[0m \033[33m%s\033[0m\n",
        minishell->pid == PARENT ? "PARENT" : "CHILD");
    fprintf(stderr, "\033[1m▶ User input:\033[0m \033[33m%s\033[0m\n",
        minishell->user_input ? minishell->user_input : "(null)");
    fprintf(stderr, "\033[1m▶ Command path:\033[0m \033[33m%s\033[0m\n",
        minishell->cmd_path ? minishell->cmd_path : "(null)");
    fprintf(stderr, "\033[1m▶ Built-in type:\033[0m ");
    if (minishell->built_in_type == FT_NULL)
        fprintf(stderr, "\033[33mNULL\033[0m\n");
    else if (minishell->built_in_type == FT_EXIT)
        fprintf(stderr, "\033[33mEXIT\033[0m\n");
    else if (minishell->built_in_type == FT_ECHO)
        fprintf(stderr, "\033[33mECHO\033[0m\n");
    else if (minishell->built_in_type == FT_CD)
        fprintf(stderr, "\033[33mCD\033[0m\n");
    else if (minishell->built_in_type == FT_PWD)
        fprintf(stderr, "\033[33mPWD\033[0m\n");
    else if (minishell->built_in_type == FT_EXPORT)
        fprintf(stderr, "\033[33mEXPORT\033[0m\n");
    else if (minishell->built_in_type == FT_UNSET)
        fprintf(stderr, "\033[33mUNSET\033[0m\n");
    else if (minishell->built_in_type == FT_ENV)
        fprintf(stderr, "\033[33mENV\033[0m\n");
    else
        fprintf(stderr, "\033[33mUNKNOWN (%d)\033[0m\n", minishell->built_in_type);
    fprintf(stderr, "\033[1m▶ Return flag:\033[0m \033[33m%s\033[0m\n",
        minishell->return_flag ? "true" : "false");
    fprintf(stderr, "\033[1m▶ Invalid_file:\033[0m \033[33m%s\033[0m\n",
        minishell->invalid_file ? "true" : "false");
    fprintf(stderr, "\n\033[1m▶ Pipe count:\033[0m \033[33m%d\033[0m\n",
        minishell->pipe_tools.redir_count);
    fprintf(stderr, "\033[1m▶ Redirection:\033[0m ");
    if (minishell->redirection == PIPE)
        fprintf(stderr, "\033[33m|\033[0m\n");
    else if (minishell->redirection == REDIR_IN)
        fprintf(stderr, "\033[33m<\033[0m\n");
    else if (minishell->redirection == REDIR_OUT)
        fprintf(stderr, "\033[33m>\033[0m\n");
    else if (minishell->redirection == REDIR_APPEND)
        fprintf(stderr, "\033[33m>>\033[0m\n");
    else if (minishell->redirection == REDIR_HEREDOC)
        fprintf(stderr, "\033[33m<<\033[0m\n");
    else
        fprintf(stderr, "\033[33mNONE\033[0m\n");
    fprintf(stderr, "\033[1m▶ Previous Redirection:\033[0m ");
    if (minishell->prev_redir == PIPE)
        fprintf(stderr, "\033[33m|\033[0m\n");
    else if (minishell->prev_redir == REDIR_IN)
        fprintf(stderr, "\033[33m<\033[0m\n");
    else if (minishell->prev_redir == REDIR_OUT)
        fprintf(stderr, "\033[33m>\033[0m\n");
    else if (minishell->prev_redir == REDIR_APPEND)
        fprintf(stderr, "\033[33m>>\033[0m\n");
    else if (minishell->prev_redir == REDIR_HEREDOC)
        fprintf(stderr, "\033[33m<<\033[0m\n");
    else
        fprintf(stderr, "\033[33mNONE\033[0m\n");
    fprintf(stderr, "\n\033[1m▶ Input matrix:\033[0m\n");
    if (minishell->input_matrix)
    {
        i = 0;
        while (minishell->input_matrix[i])
        {
            fprintf(stderr, "  [%d]: \033[33m%s\033[0m\n", i,
                minishell->input_matrix[i]);
            i++;
        }
    }
    else
        fprintf(stderr, "  \033[33m(null)\033[0m\n");
        
    fprintf(stderr, "\n\033[1m▶ Exit status ($?):\033[0m \033[33m%d\033[0m\n",
            minishell->exit_status);
        
    fprintf(stderr, "\n\033[1;36m===========================\033[0m\n");
}
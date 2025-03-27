/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:50:46 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/27 12:24:58 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(t_minishell *minishell, char **envp)
{
	// suggest: cambiar nombre a set_envp -> checkpoint()?
	set_envp(minishell, envp);
	minishell->user = ft_getenv(minishell->envp, "USER=");
	minishell->pid = PARENT;
	store_pipes(minishell);
}

void	set_envp(t_minishell *minishell, char **envp)
{
	bool	flag;
	char	**envp_matrix;
	int		last_exit_status; // suggest: añadido

	flag = false;
	last_exit_status = 0;
	if (minishell->envp)
	{
		flag = true;
		envp_matrix = matrix_cpy(minishell->envp, 0);
		free_matrix(minishell->envp);
	}

	// suggest
	if (minishell->exit_status) // si existe, guardamos el estado de salida
		last_exit_status = minishell->exit_status;
	ft_memset(minishell, 0, sizeof(t_minishell));
	if (flag)
	{
		minishell->envp = matrix_cpy(envp_matrix, 0);
		free_matrix(envp_matrix);
	}
	else
		minishell->envp = matrix_cpy(envp, 0);

	// suggest
	if (last_exit_status)
		minishell->exit_status = last_exit_status;

	minishell->pid = 1;
}

char    *ft_getenv(char **envp, char *env_var)
{
    int i;
    int len;

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
	if (minishell->shell_prompt.prompt)
		free(minishell->shell_prompt.prompt);
}

// suggest
void print_minishell(t_minishell *minishell)
{
    int i;

    printf("\n\033[1;36m--- MINISHELL PID:%d INFO ---\033[0m\n\n", minishell->pid);
    
    // Información general
    printf("\033[1m▶ User:\033[0m \033[33m%s\033[0m\n", minishell->user ? minishell->user : "(null)");
    printf("\033[1m▶ User input:\033[0m \033[33m%s\033[0m\n", minishell->user_input ? minishell->user_input : "(null)");
    printf("\033[1m▶ Arguments count:\033[0m \033[33m%d\033[0m\n", minishell->args_num);
    printf("\033[1m▶ Command path:\033[0m \033[33m%s\033[0m\n", minishell->cmd_path ? minishell->cmd_path : "(null)");
    printf("\033[1m▶ Exit status ($?):\033[0m \033[33m%d\033[0m\n", minishell->exit_status);
	printf("\033[1m▶ Redirection:\033[0m \033[33m%d\033[0m\n", minishell->redirection);
	//printf("\033[1m▶ Read pipe:\033[0m \033[33m%d\033[0m\n", minishell->pipes.pipe.read_pipe);
	//printf("\033[1m▶ Write pipe:\033[0m \033[33m%d\033[0m\n", minishell->pipes.pipe.write_pipe);
	//printf("\033[1m▶ Pipe number:\033[0m \033[33m%d\033[0m\n", minishell->pipes.pipe_count);
	printf("\033[1m▶ First command:\033[0m \033[33m%d\033[0m\n", minishell->first_cmd);

    // Tipo de built-in usando if en lugar de switch
    printf("\033[1m▶ Built-in type:\033[0m ");
    if (minishell->built_in_type == FT_NULL)
        printf("\033[33mNULL\033[0m\n");
    else if (minishell->built_in_type == FT_EXIT)
        printf("\033[33mEXIT\033[0m\n");
    else if (minishell->built_in_type == FT_ECHO)
        printf("\033[33mECHO\033[0m\n");
    else if (minishell->built_in_type == FT_CD)
        printf("\033[33mCD\033[0m\n");
    else if (minishell->built_in_type == FT_PWD)
        printf("\033[33mPWD\033[0m\n");
    else if (minishell->built_in_type == FT_EXPORT)
        printf("\033[33mEXPORT\033[0m\n");
    else if (minishell->built_in_type == FT_UNSET)
        printf("\033[33mUNSET\033[0m\n");
    else if (minishell->built_in_type == FT_ENV)
        printf("\033[33mENV\033[0m\n");
    else
        printf("\033[33mUNKNOWN (%d)\033[0m\n", minishell->built_in_type);
    
    // Matriz de entrada
    printf("\n\033[1m▶ Input matrix:\033[0m\n");
    if (minishell->input_matrix)
    {
        i = 0;
        while (minishell->input_matrix[i])
        {
            printf("  [%d]: \033[33m'%s'\033[0m\n", i, minishell->input_matrix[i]);
            i++;
        }
    }
    else
        printf("  \033[33m(null)\033[0m\n");
       
    /* // Variables de entorno
    printf("\n\033[1m▶ Environment variables:\033[0m\n");
    if (minishell->envp)
    {
        i = 0;
        while (minishell->envp[i])
        {
            printf("  [%d]: \033[33m%s\033[0m\n", i, minishell->envp[i]);
            i++;
        }
    }
    else
        printf("  \033[33m(null)\033[0m\n"); */
    
    printf("\n\033[1;36m---------------------------\033[0m\n");
}